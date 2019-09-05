#include "add_dialog.h"
#include "global_variables.h"

#include <QtWidgets>
add_dialog::add_dialog(QWidget *parent)
    :QDialog (parent)
{
     billIdLabel = new QLabel("Bill #");
     rentLabel = new QLabel("Rent");
     electricityLabel = new QLabel("Electricity");
     waterLabel =  new QLabel("Water");
     gasLabel =  new QLabel("Gas");
     internetLabel = new QLabel("Internet");
     totalLabel = new QLabel("Total Due");
     dateAddedLabel = new QLabel("Date Added");
     dateDueLabel= new QLabel("Date Due");


     okButton = new QPushButton("OK");
     cancelButton = new QPushButton("CANCEL");

     billIdText = new QLineEdit;
     rentText = new QDoubleSpinBox;
     electricityText = new QDoubleSpinBox;
     waterText = new QDoubleSpinBox;
     gasText =new QDoubleSpinBox;
     internetText = new QDoubleSpinBox;
     totalText = new QLineEdit;
     dateAddedText = new QLineEdit;
     dateDueText = new QLineEdit;

     rentText->setButtonSymbols(QAbstractSpinBox::NoButtons);
     rentText->setMaximum(9999);
     rentText->setDecimals(2);
    // rentText->setPrefix("$");

     electricityText->setButtonSymbols(QAbstractSpinBox::NoButtons);
     electricityText->setMaximum(9999);
     electricityText->setDecimals(2);
    // electricityText->setPrefix("$");

     waterText->setButtonSymbols(QAbstractSpinBox::NoButtons);
     waterText->setMaximum(9999);
     waterText->setDecimals(2);
    // waterText->setPrefix("$");

     gasText->setButtonSymbols(QAbstractSpinBox::NoButtons);
     gasText->setMaximum(9999);
     gasText->setDecimals(2);
     //gasText->setPrefix("$");

     internetText->setButtonSymbols(QAbstractSpinBox::NoButtons);
     internetText->setMaximum(9999);
     internetText->setDecimals(2);
     //internetText->setPrefix("$");

     QGridLayout *gLayout = new QGridLayout;
     /* imagine these numbers as part of a grid,
        this will make the numbers make sense*/
     gLayout->setColumnStretch (1,2);

     billIdText->setReadOnly(true);
     billIdText->setText(QString::number((globalItemId+1)));
     gLayout->addWidget(billIdLabel, 0, 0);
     gLayout->addWidget(billIdText, 0, 1);


     gLayout->addWidget(rentLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(rentText,1, 1, Qt::AlignLeft);

     gLayout->addWidget(electricityLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(electricityText, 2, 1, Qt::AlignLeft);

     gLayout->addWidget(waterLabel, 3, 0);
     gLayout->addWidget(waterText, 3, 1);

     gLayout->addWidget(gasLabel, 4, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(gasText, 4, 1, Qt::AlignLeft);

     gLayout->addWidget(internetLabel, 5, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(internetText, 5, 1, Qt::AlignLeft);

     totalText->setReadOnly(true);
     gLayout->addWidget(totalLabel, 6, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(totalText, 6, 1, Qt::AlignLeft);

     QDate date;
     dateAddedText->setReadOnly(true);
     dateAddedText->setText(date.currentDate().toString());
     gLayout->addWidget(dateAddedLabel,7, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(dateAddedText, 7, 1, Qt::AlignLeft);

     gLayout->addWidget(dateDueLabel, 8, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(dateDueText, 8, 1, Qt::AlignLeft);



     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(okButton);
     buttonLayout->addWidget(cancelButton);

     gLayout->addLayout(buttonLayout, 9, 1, Qt::AlignRight);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(gLayout);
     setLayout(mainLayout);

     connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
     connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

     setWindowTitle(tr("Bills due this month"));
}
