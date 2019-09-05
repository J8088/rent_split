#include "add_dialog.h"
#include "newitemtab.h"

#include <QtWidgets>
newitemtab::newitemtab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr ("There currently are no items in your list."
                                      "\n Click Add to add new items"));
    addButton = new QPushButton(tr("Add"));

    connect(addButton, &QAbstractButton::clicked, this, &newitemtab::addEntry);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(addButton,0,Qt::AlignCenter);

    setLayout(mainLayout);

}

void newitemtab::addEntry()
{
    add_dialog dialog;
    //ADD THIS AS YOU ADD MROE COLUMNS
    if(dialog.exec()){
        int billId=dialog.billIdText->text().toInt();
        double rent=dialog.rentText->text().toDouble();
        double electricity=dialog.electricityText->text().toDouble();
        double water=dialog.waterText->text().toDouble();
        double gas=dialog.gasText->text().toDouble();
        double internet=dialog.internetText->text().toDouble();
        double total=dialog.totalText->text().toDouble();


        QString dateAdded = dialog.dateAddedText->text();
        QString dateDue = dialog.dateDueText->text();
        emit sendDetails(billId,rent,electricity,water,gas,internet,total,dateAdded,dateDue);
    }
}
