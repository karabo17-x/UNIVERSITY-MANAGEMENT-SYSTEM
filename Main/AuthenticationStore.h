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
