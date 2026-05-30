#include "StudentSearchDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QColor>
#include <QDebug>

StudentSearchDialog::StudentSearchDialog(Administration* admin, QWidget* parent)
    : QDialog(parent), admin(admin) {
    setWindowTitle("Search Student");
    setModal(true);
    setGeometry(200, 200, 500, 300);
    setupUI();
}

void StudentSearchDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("Search Student by ID");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(new QLabel("Student ID:"));
    searchEdit = new QLineEdit();
    searchEdit->setStyleSheet("QLineEdit { color: #000000; background-color: #FFFFFF; border: 1px solid #CCCCCC; padding: 5px; }");
    searchEdit->setFont(QFont("DejaVu Sans", 11));
    QPalette searchPalette;
    searchPalette.setColor(QPalette::Text, QColor(0, 0, 0));
    searchPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    searchEdit->setPalette(searchPalette);
    connect(searchEdit, &QLineEdit::textChanged, this, [](const QString &s){ qDebug() << "searchEdit:textChanged:" << s << "hex:" << s.toUtf8().toHex(); });
    searchLayout->addWidget(searchEdit);
    
    QPushButton* searchButton = new QPushButton("Search");
    connect(searchButton, &QPushButton::clicked, this, &StudentSearchDialog::onSearch);
    searchLayout->addWidget(searchButton);
    
    mainLayout->addLayout(searchLayout);
    mainLayout->addSpacing(10);
    
    resultDisplay = new QTextEdit();
    resultDisplay->setReadOnly(true);
    mainLayout->addWidget(resultDisplay);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton* closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &StudentSearchDialog::onCancel);
    buttonLayout->addWidget(closeButton);
    
    mainLayout->addLayout(buttonLayout);

    // Log search edit properties for debugging
    qDebug() << "searchEdit properties:" 
             << "text=" << searchEdit->text()
             << "echoMode=" << searchEdit->echoMode()
             << "inputMask=" << searchEdit->inputMask()
             << "readOnly=" << searchEdit->isReadOnly()
             << "fontFamily=" << searchEdit->font().family()
             << "fontPointSize=" << searchEdit->font().pointSizeF();
}

void StudentSearchDialog::onSearch() {
    QString studentId = searchEdit->text();
    if (studentId.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a Student ID.");
        return;
    }
    
    Student* student = admin->searchStudent(studentId.toStdString());
    if (student) {
        QString info = QString(
            "Student ID: %1\n"
            "Name: %2\n"
            "Email: %3\n"
            "Phone: %4\n"
            "Roll Number: %5\n"
            "Major: %6\n"
            "GPA: %7"
        ).arg(
            QString::fromStdString(student->getId()),
            QString::fromStdString(student->getName()),
            QString::fromStdString(student->getEmail()),
            QString::fromStdString(student->getPhone()),
            QString::fromStdString(student->getRollNumber()),
            QString::fromStdString(student->getMajor()),
            QString::number(student->getGPA())
        );
        resultDisplay->setText(info);
    } else {
        resultDisplay->setText("Student not found.");
    }
}

void StudentSearchDialog::onCancel() {
    reject();
}
