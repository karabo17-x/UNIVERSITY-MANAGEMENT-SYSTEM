#ifndef STUDENT_REGISTRATION_DIALOG_H
#define STUDENT_REGISTRATION_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <memory>
#include "../Administration/Administration.h"

class StudentRegistrationDialog : public QDialog {
    Q_OBJECT

public:
    StudentRegistrationDialog(Administration* admin, QWidget* parent = nullptr);

private slots:
    void onRegister();
    void onCancel();

private:
    Administration* admin;
    
    QLineEdit* studentIdEdit;
    QLineEdit* nameEdit;
    QLineEdit* emailEdit;
    QLineEdit* phoneEdit;
    QLineEdit* rollNumberEdit;
    QLineEdit* majorEdit;
    QLineEdit* gpaEdit;
    
    void setupUI();
    bool validateInputs();
};

#endif
