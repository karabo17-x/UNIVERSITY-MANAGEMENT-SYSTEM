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
