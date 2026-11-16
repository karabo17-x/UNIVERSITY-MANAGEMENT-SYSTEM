#include "AuthenticationDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
QLineEdit *passwordField(QWidget *parent) {
    auto *field = new QLineEdit(parent);
    field->setEchoMode(QLineEdit::Password);
    field->setMinimumHeight(36);
    return field;
}
}

bool AuthenticationDialog::run(AuthenticationStore *store, AuthenticatedUser *user, QWidget *parent) {
    if (!store || !store->isReady()) {
        QMessageBox::critical(parent, "Account database unavailable",
            store ? store->lastError() : "The account database could not be opened.");
        return false;
    }

    const bool firstRun = store->accountCount() == 0;
    QDialog dialog(parent);
    dialog.setModal(true);
    dialog.setMinimumWidth(440);
    dialog.setWindowTitle(firstRun ? "Create the first administrator account" : "Sign in to University Management System");

    auto *layout = new QVBoxLayout(&dialog);
