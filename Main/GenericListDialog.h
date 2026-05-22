#ifndef GENERIC_LIST_DIALOG_H
#define GENERIC_LIST_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QString>
#include <QStringList>

class GenericListDialog : public QDialog {
    Q_OBJECT

public:
    GenericListDialog(const QString& title, const QStringList& items, QWidget* parent = nullptr);

private:
    QListWidget* listWidget;
};

#endif
