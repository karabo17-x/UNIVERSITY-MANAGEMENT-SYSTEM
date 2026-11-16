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

