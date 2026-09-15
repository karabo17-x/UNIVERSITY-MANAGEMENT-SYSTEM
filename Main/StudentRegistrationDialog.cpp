#include "StudentRegistrationDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPalette>
#include <QColor>
#include <QFont>
#include <memory>
#include "../Student/Student.h"

StudentRegistrationDialog::StudentRegistrationDialog(Administration* admin, QWidget* parent)
    : QDialog(parent), admin(admin) {
    setWindowTitle("Register New Student");
    setModal(true);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setFixedSize(560, 460);
    setObjectName("studentRegistrationDialog");
    setupUI();
}

void StudentRegistrationDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(28, 26, 28, 24);
    mainLayout->setSpacing(14);
    
    QLabel* titleLabel = new QLabel("Student Registration Form");
    titleLabel->setObjectName("dialogTitle");
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(12);
    gridLayout->setVerticalSpacing(9);
    gridLayout->setColumnStretch(1, 1);
    
    // Keep input fields readable regardless of the desktop theme.
    auto setupLineEdit = [](QLineEdit* edit) {
        edit->setMinimumHeight(34);
        edit->setStyleSheet("QLineEdit { color: #282832; background: #ffffff; border: 1px solid #cfc9d5; border-radius: 5px; padding: 0 9px; } QLineEdit:focus { border: 2px solid #6f168d; }");
        edit->setFont(QFont("Segoe UI", 10));
        QPalette palette;
        palette.setColor(QPalette::Text, QColor(0, 0, 0));
        palette.setColor(QPalette::Base, QColor(255, 255, 255));
        edit->setPalette(palette);
    };
    
    gridLayout->addWidget(new QLabel("Student ID:"), 0, 0);
    studentIdEdit = new QLineEdit();
    setupLineEdit(studentIdEdit);
    gridLayout->addWidget(studentIdEdit, 0, 1);
    
    gridLayout->addWidget(new QLabel("Name:"), 1, 0);
    nameEdit = new QLineEdit();
    setupLineEdit(nameEdit);
    gridLayout->addWidget(nameEdit, 1, 1);
    
    gridLayout->addWidget(new QLabel("Email:"), 2, 0);
    emailEdit = new QLineEdit();
    setupLineEdit(emailEdit);
    gridLayout->addWidget(emailEdit, 2, 1);
    
    gridLayout->addWidget(new QLabel("Phone:"), 3, 0);
    phoneEdit = new QLineEdit();
    setupLineEdit(phoneEdit);
    gridLayout->addWidget(phoneEdit, 3, 1);
    
    gridLayout->addWidget(new QLabel("Roll Number:"), 4, 0);
    rollNumberEdit = new QLineEdit();
    setupLineEdit(rollNumberEdit);
    gridLayout->addWidget(rollNumberEdit, 4, 1);
    
    gridLayout->addWidget(new QLabel("Major:"), 5, 0);
    majorEdit = new QLineEdit();
    setupLineEdit(majorEdit);
    gridLayout->addWidget(majorEdit, 5, 1);
    
    gridLayout->addWidget(new QLabel("GPA:"), 6, 0);
    gpaEdit = new QLineEdit("0.0");
    setupLineEdit(gpaEdit);
    gridLayout->addWidget(gpaEdit, 6, 1);
    
    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacing(15);


    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton* registerButton = new QPushButton("Register");
    registerButton->setMinimumSize(112, 38);
    registerButton->setObjectName("primaryDialogButton");
    connect(registerButton, &QPushButton::clicked, this, &StudentRegistrationDialog::onRegister);
    buttonLayout->addWidget(registerButton);
    
    QPushButton* cancelButton = new QPushButton("Cancel");
    cancelButton->setMinimumSize(100, 38);
    cancelButton->setObjectName("secondaryDialogButton");
    connect(cancelButton, &QPushButton::clicked, this, &StudentRegistrationDialog::onCancel);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);

    setStyleSheet(R"(
        QDialog#studentRegistrationDialog { background: #f8f7fa; }
        QLabel { color: #30303a; font-size: 14px; }
        QLabel#dialogTitle { color: #6f168d; font-size: 21px; font-weight: 700; padding-bottom: 4px; }
        QPushButton#primaryDialogButton { background: #6f168d; color: white; border: 0; border-radius: 5px; font-weight: 700; }
        QPushButton#primaryDialogButton:hover { background: #581270; }
        QPushButton#secondaryDialogButton { background: #ffffff; color: #4d4d58; border: 1px solid #bdb9c4; border-radius: 5px; font-weight: 600; }
        QPushButton#secondaryDialogButton:hover { background: #f0edf3; border-color: #6f168d; color: #6f168d; }
    )");
}

bool StudentRegistrationDialog::validateInputs() {
    if (studentIdEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Student ID is required.");
        return false;
    }
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name is required.");
        return false;
    }
    if (emailEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Email is required.");
        return false;
    }
    if (phoneEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Phone is required.");
        return false;
    }
    return true;
}

void StudentRegistrationDialog::onRegister() {
    if (!validateInputs()) return;
    
    try {
        auto newStudent = std::make_unique<Student>(
            studentIdEdit->text().toStdString(),
            nameEdit->text().toStdString(),
            emailEdit->text().toStdString(),
            phoneEdit->text().toStdString(),
            rollNumberEdit->text().toStdString(),
            majorEdit->text().toStdString()
        );
        newStudent->setGPA(gpaEdit->text().toDouble());
        
        if (!admin->registerStudent(std::move(newStudent))) {
            QMessageBox::warning(this, "Registration Failed", "A student with this ID is already registered.");
            return;
        }
        QMessageBox::information(this, "Success", "Student registered successfully!");
        accept();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to register student: %1").arg(e.what()));
    }
}

void StudentRegistrationDialog::onCancel() {
    reject();
}
