#ifndef STUDENT_SEARCH_DIALOG_H
#define STUDENT_SEARCH_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "../Administration/Administration.h"

class StudentSearchDialog : public QDialog {
    Q_OBJECT

public:
    StudentSearchDialog(Administration* admin, QWidget* parent = nullptr);

private slots:
    void onSearch();
    void onCancel();

private:
    Administration* admin;
    QLineEdit* searchEdit;
    QTextEdit* resultDisplay;
    
    void setupUI();
};

#endif
