#ifndef AUTHENTICATION_DIALOG_H
#define AUTHENTICATION_DIALOG_H

#include <QDialog>
#include "AuthenticationStore.h"

class AuthenticationDialog {
public:
    static bool run(AuthenticationStore *store, AuthenticatedUser *user, QWidget *parent = nullptr);
};

#endif
