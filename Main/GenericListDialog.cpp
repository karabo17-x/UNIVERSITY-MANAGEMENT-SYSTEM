#include "GenericListDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

GenericListDialog::GenericListDialog(const QString& title, const QStringList& items, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle(title);
    setModal(true);
    setGeometry(200, 200, 600, 400);
    
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    listWidget = new QListWidget();
    listWidget->addItems(items);
    layout->addWidget(listWidget);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    QPushButton* closeButton = new QPushButton("Close");
    closeButton->setMinimumWidth(100);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    buttonLayout->addWidget(closeButton);
    
    layout->addLayout(buttonLayout);
}
