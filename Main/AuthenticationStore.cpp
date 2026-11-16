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
