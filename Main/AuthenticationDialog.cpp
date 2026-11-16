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
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(14);
    auto *title = new QLabel(firstRun ? "Set up your university administrator" : "Sign in");
    title->setStyleSheet("font-size: 22px; font-weight: 700; color: #174f83;");
    layout->addWidget(title);
    auto *message = new QLabel(firstRun
        ? "This first account will manage staff accounts and university services. Choose a strong password."
        : "Use the username and password assigned to your university account.");
    message->setWordWrap(true);
    message->setStyleSheet("color: #4b5563;");
    layout->addWidget(message);

    auto *form = new QFormLayout();
    form->setSpacing(10);
