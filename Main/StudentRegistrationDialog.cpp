#include "StudentRegistrationDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPalette>
#include <QColor>
#include <QDebug>
#include <QFont>
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
    
    // Helper lambda to setup QLineEdit with both stylesheet and palette
    auto setupLineEdit = [](QLineEdit* edit) {
        edit->setStyleSheet("QLineEdit { color: #000000; background-color: #FFFFFF; border: 1px solid #CCCCCC; padding: 5px; }");
        edit->setFont(QFont("DejaVu Sans", 11));
        QPalette palette;
        palette.setColor(QPalette::Text, QColor(0, 0, 0));
        palette.setColor(QPalette::Base, QColor(255, 255, 255));
        edit->setPalette(palette);
    };
    
    gridLayout->addWidget(new QLabel("Student ID:"), 0, 0);
    studentIdEdit = new QLineEdit();
    setupLineEdit(studentIdEdit);
    connect(studentIdEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "studentIdEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(studentIdEdit, 0, 1);
    
    gridLayout->addWidget(new QLabel("Name:"), 1, 0);
    nameEdit = new QLineEdit();
    setupLineEdit(nameEdit);
    connect(nameEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "nameEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(nameEdit, 1, 1);
    
    gridLayout->addWidget(new QLabel("Email:"), 2, 0);
    emailEdit = new QLineEdit();
    setupLineEdit(emailEdit);
    connect(emailEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "emailEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(emailEdit, 2, 1);
    
    gridLayout->addWidget(new QLabel("Phone:"), 3, 0);
    phoneEdit = new QLineEdit();
    setupLineEdit(phoneEdit);
    connect(phoneEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "phoneEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(phoneEdit, 3, 1);
    
    gridLayout->addWidget(new QLabel("Roll Number:"), 4, 0);
    rollNumberEdit = new QLineEdit();
    setupLineEdit(rollNumberEdit);
    connect(rollNumberEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "rollNumberEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(rollNumberEdit, 4, 1);
    
    gridLayout->addWidget(new QLabel("Major:"), 5, 0);
    majorEdit = new QLineEdit();
    setupLineEdit(majorEdit);
    connect(majorEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "majorEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(majorEdit, 5, 1);
    
    gridLayout->addWidget(new QLabel("GPA:"), 6, 0);
    gpaEdit = new QLineEdit("0.0");
    setupLineEdit(gpaEdit);
    connect(gpaEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "gpaEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    gridLayout->addWidget(gpaEdit, 6, 1);
    
    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacing(15);

    // Log QLineEdit properties to help debug rendering issues
    auto logEditProps = [](QLineEdit* e, const char* name){
        qDebug() << name
                 << "text()=" << e->text()
                 << "echoMode=" << e->echoMode()
                 << "inputMask=" << e->inputMask()
                 << "readOnly=" << e->isReadOnly()
                 << "fontFamily=" << e->font().family()
                 << "fontPointSize=" << e->font().pointSizeF()
                 << "palette.Text=" << e->palette().color(QPalette::Text).name()
                 << "palette.Base=" << e->palette().color(QPalette::Base).name();
    };
    logEditProps(studentIdEdit, "studentIdEdit");
    logEditProps(nameEdit, "nameEdit");
    logEditProps(emailEdit, "emailEdit");
    logEditProps(phoneEdit, "phoneEdit");
    logEditProps(rollNumberEdit, "rollNumberEdit");
    logEditProps(majorEdit, "majorEdit");
    logEditProps(gpaEdit, "gpaEdit");
    // Optionally auto-fill fields for debug reproduction
    if (qEnvironmentVariableIsSet("AUTO_FILL")) {
        studentIdEdit->setText("STU001");
        nameEdit->setText("John Doe");
        emailEdit->setText("john@example.com");
        phoneEdit->setText("5551234");
        rollNumberEdit->setText("2024001");
        majorEdit->setText("Computer Science");
        gpaEdit->setText("3.8");
    }
    // Log values after optional auto-fill
    qDebug() << "After AUTO_FILL:";
    logEditProps(studentIdEdit, "studentIdEdit");
    logEditProps(nameEdit, "nameEdit");
    logEditProps(emailEdit, "emailEdit");
    logEditProps(phoneEdit, "phoneEdit");
    logEditProps(rollNumberEdit, "rollNumberEdit");
    logEditProps(majorEdit, "majorEdit");
    logEditProps(gpaEdit, "gpaEdit");

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
