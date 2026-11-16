#include "AuthenticationStore.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStringList>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

namespace {
constexpr int SaltLength = 16;
constexpr int HashLength = 32;
constexpr int Pbkdf2Iterations = 310000;

bool derivePasswordHash(const QString &password, const QByteArray &salt, QByteArray *hash) {
    const QByteArray passwordUtf8 = password.toUtf8();
    QByteArray result(HashLength, Qt::Uninitialized);
    if (PKCS5_PBKDF2_HMAC(passwordUtf8.constData(), passwordUtf8.size(),
                          reinterpret_cast<const unsigned char *>(salt.constData()), salt.size(),
                          Pbkdf2Iterations, EVP_sha256(), HashLength,
                          reinterpret_cast<unsigned char *>(result.data())) != 1) {
        return false;
    }
    *hash = result;
    return true;
}

QString normalizedUsername(const QString &username) {
    return username.trimmed().toLower();
}

void setError(QString *error, const QString &message) {
    if (error) *error = message;
}
}

AuthenticationStore::AuthenticationStore(const QString &databasePath) {
    const QString databaseDirectory = QFileInfo(databasePath).absolutePath();
    QDir().mkpath(databaseDirectory);
    QFile::setPermissions(databaseDirectory,
        QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
    const QByteArray path = QFile::encodeName(databasePath);
    const int result = sqlite3_open_v2(path.constData(), &database,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, nullptr);
    if (result != SQLITE_OK) {
        errorMessage = database ? QString::fromUtf8(sqlite3_errmsg(database)) : "Could not open the account database.";
        if (database) sqlite3_close(database);
        database = nullptr;
        return;
    }
    sqlite3_busy_timeout(database, 5000);
    const char *schema =
        "CREATE TABLE IF NOT EXISTS accounts ("
        " username TEXT PRIMARY KEY COLLATE NOCASE,"
        " full_name TEXT NOT NULL,"
        " role TEXT NOT NULL CHECK(role IN ('student','lecturer','administrator','registrar','residence','sports'))," 
        " linked_id TEXT NOT NULL DEFAULT '',"
        " password_salt TEXT NOT NULL,"
        " password_hash TEXT NOT NULL,"
        " created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
        ");";
    char *message = nullptr;
    if (sqlite3_exec(database, schema, nullptr, nullptr, &message) != SQLITE_OK) {
        errorMessage = QString::fromUtf8(message ? message : sqlite3_errmsg(database));
        sqlite3_free(message);
        sqlite3_close(database);
        database = nullptr;
        return;
    }
    QFile databaseFile(databasePath);
    if (databaseFile.exists()) databaseFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
}

AuthenticationStore::~AuthenticationStore() {
    if (database) sqlite3_close(database);
}

bool AuthenticationStore::isReady() const {
    return database != nullptr;
}

QString AuthenticationStore::lastError() const {
    return errorMessage;
}

int AuthenticationStore::accountCount() const {
    if (!database) return 0;
    sqlite3_stmt *statement = nullptr;
    if (sqlite3_prepare_v2(database, "SELECT COUNT(*) FROM accounts", -1, &statement, nullptr) != SQLITE_OK) return 0;
    int count = 0;
    if (sqlite3_step(statement) == SQLITE_ROW) count = sqlite3_column_int(statement, 0);
    sqlite3_finalize(statement);
    return count;
}

QStringList AuthenticationStore::accountSummaries() const {
    QStringList accounts;
    if (!database) return accounts;
    sqlite3_stmt *statement = nullptr;
    const char *sql = "SELECT username,full_name,role,linked_id FROM accounts ORDER BY role,full_name";
    if (sqlite3_prepare_v2(database, sql, -1, &statement, nullptr) != SQLITE_OK) return accounts;
    while (sqlite3_step(statement) == SQLITE_ROW) {
        const auto value = [statement](int column) {
            const auto *text = sqlite3_column_text(statement, column);
            return QString::fromUtf8(reinterpret_cast<const char *>(text ? text : reinterpret_cast<const unsigned char *>("")));
        };
        QString line = QString("%1 · %2 · %3").arg(value(1), value(0), value(2));
        if (!value(3).isEmpty()) line += QString(" · ID %1").arg(value(3));
        accounts.append(line);
    }
    sqlite3_finalize(statement);
    return accounts;
}

bool AuthenticationStore::createAccount(const QString &username, const QString &password,
                                        const QString &fullName, const QString &role,
                                        const QString &linkedId, QString *error) {
    if (!database) { setError(error, errorMessage); return false; }
    const QString cleanUsername = normalizedUsername(username);
    const QString cleanName = fullName.trimmed();
    static const QRegularExpression usernamePattern("^[a-z0-9._-]{3,64}$");
    static const QStringList acceptedRoles = {"student", "lecturer", "administrator", "registrar", "residence", "sports"};
    if (!usernamePattern.match(cleanUsername).hasMatch()) {
        setError(error, "Username must be 3–64 characters and use letters, numbers, dots, underscores or hyphens.");
