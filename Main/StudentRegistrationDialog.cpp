#include "StudentRegistrationDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "../Student/Student.h"

StudentRegistrationDialog::StudentRegistrationDialog(Administration* admin, QWidget* parent)
    : QDialog(parent), admin(admin) {
    setWindowTitle("Register New Student");
    setModal(true);
    setGeometry(200, 200, 500, 450);
    setupUI();
}

void StudentRegistrationDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("Student Registration Form");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    
    QGridLayout* gridLayout = new QGridLayout();
    
    gridLayout->addWidget(new QLabel("Student ID:"), 0, 0);
    studentIdEdit = new QLineEdit();
    gridLayout->addWidget(studentIdEdit, 0, 1);
    
    gridLayout->addWidget(new QLabel("Name:"), 1, 0);
    nameEdit = new QLineEdit();
    gridLayout->addWidget(nameEdit, 1, 1);
    
    gridLayout->addWidget(new QLabel("Email:"), 2, 0);
    emailEdit = new QLineEdit();
    gridLayout->addWidget(emailEdit, 2, 1);
    
    gridLayout->addWidget(new QLabel("Phone:"), 3, 0);
    phoneEdit = new QLineEdit();
    gridLayout->addWidget(phoneEdit, 3, 1);
    
    gridLayout->addWidget(new QLabel("Roll Number:"), 4, 0);
    rollNumberEdit = new QLineEdit();
    gridLayout->addWidget(rollNumberEdit, 4, 1);
    
    gridLayout->addWidget(new QLabel("Major:"), 5, 0);
    majorEdit = new QLineEdit();
    gridLayout->addWidget(majorEdit, 5, 1);
    
    gridLayout->addWidget(new QLabel("GPA:"), 6, 0);
    gpaEdit = new QLineEdit("0.0");
    gridLayout->addWidget(gpaEdit, 6, 1);
    
    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacing(15);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton* registerButton = new QPushButton("Register");
    registerButton->setMinimumWidth(100);
    registerButton->setStyleSheet("QPushButton { background-color: #1a5490; color: white; padding: 5px; }");
    connect(registerButton, &QPushButton::clicked, this, &StudentRegistrationDialog::onRegister);
    buttonLayout->addWidget(registerButton);
    
    QPushButton* cancelButton = new QPushButton("Cancel");
    cancelButton->setMinimumWidth(100);
    connect(cancelButton, &QPushButton::clicked, this, &StudentRegistrationDialog::onCancel);
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
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
        Student* newStudent = new Student(
            studentIdEdit->text().toStdString(),
            nameEdit->text().toStdString(),
            emailEdit->text().toStdString(),
            phoneEdit->text().toStdString(),
            rollNumberEdit->text().toStdString(),
            majorEdit->text().toStdString()
        );
        newStudent->setGPA(gpaEdit->text().toDouble());
        
        admin->registerStudent(newStudent);
        QMessageBox::information(this, "Success", "Student registered successfully!");
        accept();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to register student: %1").arg(e.what()));
    }
}

void StudentRegistrationDialog::onCancel() {
    reject();
}
