#include "AuthenticationDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <memory>
#include "../Student/Student.h"

namespace {
QLineEdit *lineField(QWidget *parent, bool secret = false) {
    auto *field = new QLineEdit(parent);
    field->setMinimumHeight(36);
    if (secret) field->setEchoMode(QLineEdit::Password);
    return field;
}

void styleForm(QDialog &dialog) {
    dialog.setStyleSheet(R"(
        QDialog { background: #f5f7fb; }
        QLabel { color: #303744; }
        QLineEdit { color: #202632; background: #ffffff; border: 1px solid #b9c2ce; border-radius: 5px; padding: 6px 9px; }
        QLineEdit:focus { border: 2px solid #245f98; }
        QPushButton { color: #253246; background: #ffffff; border: 1px solid #aeb8c5; border-radius: 5px; padding: 7px 14px; min-width: 94px; min-height: 34px; font-weight: 600; }
        QPushButton:hover { background: #eaf1f8; border-color: #245f98; }
        QPushButton:default { color: #ffffff; background: #245f98; border-color: #245f98; }
        QPushButton:default:hover { background: #194c7d; }
    )");
}

bool runStudentSignup(AuthenticationStore *store, Administration *administration,
                      AuthenticatedUser *user, QWidget *parent) {
    QDialog dialog(parent);
    dialog.setWindowTitle("Student sign up");
    dialog.setMinimumWidth(470);
    styleForm(dialog);
    auto *layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(26, 22, 26, 20);
    layout->setSpacing(12);
    auto *title = new QLabel("Create your student account");
    title->setStyleSheet("font-size: 21px; font-weight: 700; color: #174f83;");
    layout->addWidget(title);

    auto *form = new QFormLayout();
    form->setSpacing(9);
    auto *studentId = lineField(&dialog);
    auto *fullName = lineField(&dialog);
    auto *email = lineField(&dialog);
    auto *phone = lineField(&dialog);
    auto *rollNumber = lineField(&dialog);
    auto *major = lineField(&dialog);
    auto *username = lineField(&dialog);
    auto *password = lineField(&dialog, true);
    auto *confirmation = lineField(&dialog, true);
    form->addRow("Student ID", studentId);
    form->addRow("Full name", fullName);
    form->addRow("Email", email);
    form->addRow("Phone", phone);
    form->addRow("Roll number", rollNumber);
    form->addRow("Major", major);
    form->addRow("Username", username);
    form->addRow("Password", password);
    form->addRow("Confirm password", confirmation);
    layout->addLayout(form);

    auto *status = new QLabel();
    status->setWordWrap(true);
    status->setStyleSheet("color: #b42318;");
    layout->addWidget(status);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    buttons->button(QDialogButtonBox::Save)->setText("Sign up");
    buttons->button(QDialogButtonBox::Save)->setDefault(true);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    AuthenticatedUser createdUser;
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, [&] {
        const QString id = studentId->text().trimmed();
        const QString name = fullName->text().trimmed();
        const QString address = email->text().trimmed();
        const QString telephone = phone->text().trimmed();
        const QString roll = rollNumber->text().trimmed();
        const QString subject = major->text().trimmed();
        if (id.isEmpty() || name.isEmpty() || address.isEmpty() || telephone.isEmpty() || roll.isEmpty() || subject.isEmpty()) {
            status->setText("Complete all student details to continue.");
            return;
        }
        if (!address.contains('@') || !address.contains('.')) {
            status->setText("Enter a valid email address.");
            return;
        }
        if (password->text().size() < 10) {
            status->setText("Use a password with at least 10 characters.");
            return;
        }
        if (password->text() != confirmation->text()) {
            status->setText("The passwords do not match.");
            return;
        }
        if (administration->searchStudent(id.toStdString())) {
            status->setText("A student record with this ID already exists. Sign in or contact the registrar.");
            return;
        }
        QString error;
        if (!store->createAccount(username->text(), password->text(), name, "student", id, &error)) {
            status->setText(error);
            return;
        }
        auto student = std::make_unique<Student>(id.toStdString(), name.toStdString(), address.toStdString(),
                                                 telephone.toStdString(), roll.toStdString(), subject.toStdString());
        if (!administration->registerStudent(std::move(student))) {
            status->setText("The student record could not be created. Contact the administrator.");
            return;
        }
        createdUser = {username->text().trimmed().toLower(), name, "student", id};
        dialog.accept();
    });
    layout->addWidget(buttons);
    username->setFocus();
    if (dialog.exec() != QDialog::Accepted) return false;
    if (user) *user = createdUser;
    return true;
}
}

bool AuthenticationDialog::run(AuthenticationStore *store, AuthenticatedUser *user,
                               Administration *administration, QWidget *parent) {
    if (!store || !store->isReady()) {
        QMessageBox::critical(parent, "Account database unavailable",
            store ? store->lastError() : "The account database could not be opened.");
        return false;
    }

    const bool firstRun = store->accountCount() == 0;
    QDialog dialog(parent);
    dialog.setModal(true);
    dialog.setMinimumWidth(440);
    dialog.setWindowTitle(firstRun ? "Create administrator account" : "Sign in to University Management System");
    styleForm(dialog);
    auto *layout = new QVBoxLayout(&dialog);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(14);
    auto *title = new QLabel(firstRun ? "Create administrator account" : "Sign in");
    title->setStyleSheet("font-size: 22px; font-weight: 700; color: #174f83;");
    layout->addWidget(title);
    if (!firstRun) {
        auto *message = new QLabel("Use your university account or create a student account.");
        message->setWordWrap(true);
        message->setStyleSheet("color: #4b5563;");
        layout->addWidget(message);
    }

    auto *form = new QFormLayout();
    form->setSpacing(10);
    auto *username = lineField(&dialog);
    auto *fullName = lineField(&dialog);
    auto *password = lineField(&dialog, true);
    form->addRow("Username", username);
    if (firstRun) form->addRow("Full name", fullName);
    form->addRow("Password", password);
    QLineEdit *confirmation = nullptr;
    if (firstRun) {
        confirmation = lineField(&dialog, true);
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
    submit->setText(firstRun ? "Sign up" : "Sign in");
    submit->setDefault(true);
    QPushButton *signUp = firstRun ? nullptr : buttons->addButton("Sign up", QDialogButtonBox::ActionRole);
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
            password->clear();
            password->setFocus();
            return;
        }
        dialog.accept();
    });
    if (signUp) {
        QObject::connect(signUp, &QPushButton::clicked, &dialog, [&] {
            if (runStudentSignup(store, administration, &authenticated, &dialog)) dialog.accept();
        });
    }
    if (firstRun) fullName->setFocus(); else username->setFocus();
    if (dialog.exec() != QDialog::Accepted) return false;
    if (user) *user = authenticated;
    return true;
}
