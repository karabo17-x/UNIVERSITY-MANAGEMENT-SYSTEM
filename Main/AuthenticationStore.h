#ifndef AUTHENTICATION_STORE_H
#define AUTHENTICATION_STORE_H

#include <QString>
#include <QStringList>
#include <sqlite3.h>

struct AuthenticatedUser {
    QString username;
    QString fullName;
    QString role;
    QString linkedId;
};

class AuthenticationStore {
public:
    explicit AuthenticationStore(const QString &databasePath);
    ~AuthenticationStore();

    AuthenticationStore(const AuthenticationStore &) = delete;
    AuthenticationStore &operator=(const AuthenticationStore &) = delete;

    bool isReady() const;
    QString lastError() const;
    int accountCount() const;
    QStringList accountSummaries() const;
    bool createAccount(const QString &username, const QString &password,
                       const QString &fullName, const QString &role,
                       const QString &linkedId, QString *error = nullptr);
    bool authenticate(const QString &username, const QString &password,
                      AuthenticatedUser *user, QString *error = nullptr) const;
    bool changePassword(const QString &username, const QString &currentPassword,
                        const QString &newPassword, QString *error = nullptr);
