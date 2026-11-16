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
    auto *username = new QLineEdit();
    username->setMinimumHeight(36);
    auto *fullName = new QLineEdit();
    fullName->setMinimumHeight(36);
    auto *password = passwordField(&dialog);
    form->addRow("Username", username);
    if (firstRun) form->addRow("Full name", fullName);
    form->addRow("Password", password);
    QLineEdit *confirmation = nullptr;
    if (firstRun) {
        confirmation = passwordField(&dialog);
        form->addRow("Confirm password", confirmation);
    }
    layout->addLayout(form);
    auto *status = new QLabel();
    status->setWordWrap(true);
    status->setStyleSheet("color: #b42318;");
    layout->addWidget(status);

    auto *buttons = new QDialogButtonBox(firstRun ? QDialogButtonBox::Save | QDialogButtonBox::Cancel
                                                  : QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QPushButton *submit = buttons->button(firstRun ? QDialogButtonBox::Save : QDialogButtonBox::Ok);
    submit->setText(firstRun ? "Create administrator" : "Sign in");
    layout->addWidget(buttons);

    AuthenticatedUser authenticated;
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, [&] {
        QString error;
        if (firstRun) {
            if (password->text() != confirmation->text()) {
                status->setText("The passwords do not match.");
                return;
            }
            if (!store->createAccount(username->text(), password->text(), fullName->text(), "administrator", {}, &error)) {
                status->setText(error);
                return;
            }
            authenticated = {username->text().trimmed().toLower(), fullName->text().trimmed(), "administrator", {}};
        } else if (!store->authenticate(username->text(), password->text(), &authenticated, &error)) {
            status->setText(error);
