#ifndef AUTHENTICATION_DIALOG_H
#define AUTHENTICATION_DIALOG_H

#include <QDialog>
#include "AuthenticationStore.h"
#include "../Administration/Administration.h"

class AuthenticationDialog {
public:
    static bool run(AuthenticationStore *store, AuthenticatedUser *user,
                    Administration *administration, QWidget *parent = nullptr);
};

#endif
