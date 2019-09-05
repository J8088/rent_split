/* this constructor accepts a parent widget
 *  and instantiates NewAddressTab, TableModel and QSortFilterProxyModel.
 *  The NewAddressTab object, which is used to indicate that the address book is empty,
 *  is added. THIS IS ALSO WHERE YOU DECLARE THE "KEY" */
#include "add_dialog.h"
#include "item_widget.h"
#include "global_variables.h"


#include <QtWidgets>

item_widget::item_widget(QWidget *parent)
    : QTabWidget (parent)
{
    table= new tablemodel(this);
    newItemTab = new newitemtab(this);

    connect(newItemTab, &newitemtab::sendDetails, this, &item_widget::addEntry);
    //POSSIBLY CHANGE THIS SO YOU HAVE NEW TABS
    addTab(newItemTab, "Items");

    setupTabs();
}

void item_widget::showAddEntryDialog()
{
    //ADD MORE SHIT WHEN FINISHED
    //REMEBER:TYPE FIRST, COLOR SECOND, ALWAYS
    add_dialog dialog;
    if(dialog.exec()){
        //Shit with this validator only accepts positive integers.
               QRegExpValidator* positiveOnly = new QRegExpValidator(QRegExp("\\d*"), this);

               int billId = dialog.billIdText->text().toInt();


               //dialog.rentText->setValidator(positiveOnly);
               double rent = dialog.rentText->text().toDouble();
              // dialog.electricityText->setValidator(positiveOnly);
               double electricity = dialog.electricityText->text().toDouble();

              // dialog.waterText->setValidator(positiveOnly);
               double water = dialog.waterText->text().toDouble();

               //dialog.gasText->setValidator(positiveOnly);
               double gas = dialog.gasText->text().toDouble();

               //dialog.internetText->setValidator(positiveOnly);
               double internet = dialog.internetText->text().toDouble();

               double total = dialog.totalText->text().toDouble();

               QString dateAdded= dialog.dateAddedText->text();

               QString dateDue = dialog.dateDueText->text();

               addEntry(billId,rent,electricity,water,gas,internet,total,dateAdded,dateDue);
    }
}

void item_widget::addEntry(int billId,double rent, double electricity,double water, double gas,double internet,
                           double total, QString dateAdded, QString dateDue)
{
    //used to get the current date.



          QDate date;

          table->insertRows(0, 1, QModelIndex());

          QModelIndex index = table->index(0, 0, QModelIndex());
          ++globalItemId;
          billId=globalItemId;
          table->setData(index,billId, Qt::EditRole);



          index = table->index(0, 1, QModelIndex());
          table->setData(index,rent, Qt::EditRole);

          index = table->index(0, 2, QModelIndex());
          table->setData(index,electricity, Qt::EditRole);

          index = table->index(0, 3, QModelIndex());
          table->setData(index, water, Qt::EditRole);

          index = table->index(0, 4, QModelIndex());
          table->setData(index,gas, Qt::EditRole);

          index = table->index(0, 5, QModelIndex());
          table->setData(index,internet, Qt::EditRole);

          index = table->index(0, 6, QModelIndex());

          //check bottom function
          total=rent+electricity+water+gas+internet;

          table->setData(index,total, Qt::EditRole);
           totalMap[globalItemId] = total;

           index = table->index(0,8, QModelIndex());
           table->setData(index,dateDue, Qt::EditRole);


            index = table->index(0, 7, QModelIndex());

          if(dateAdded.length()==0){//If its a new entry...
          //currentdate format: tue, july 30, 2019
          dateAdded = date.currentDate().toString();
          table->setData(index,dateAdded,Qt::EditRole);
          } else {//If its NOT a new entry..
             table->setData(index,dateAdded,Qt::EditRole);
          }


         removeTab(indexOf(newItemTab));
}
//not needed atm, perhaps use it at a later date.
//double item_widget::addTotal(double rent, double electricity,double water, double gas,double internet,
//                           double total){
//       total=0;
//    int intRent=0;
//    int intElectricity=0;
//    int intWater=0;
//    int intGas=0;
//    int intInternet=0;

//    rent=rent*100;
//    rent=trunc(rent);
//    intRent=(int)rent;

//    electricity=electricity*100;
//    electricity=trunc(electricity);
//    intElectricity=(int)electricity;

//    water=water*100;
//    water=trunc(water);
//    intWater=(int)water;

//    gas=gas*100;
//    gas=trunc(gas);
//    intGas=(int)gas;

//    internet=internet*100;
//    internet=trunc(internet);
//    intInternet=(int)internet;


//    total=rent+electricity+water+gas+internet;
//   // total=total/100;
//    return total;

//}
void item_widget::editEntry()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
   QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
   QItemSelectionModel *selectionModel = temp->selectionModel();

   QModelIndexList indexes = selectionModel->selectedRows();
   //ADD MORE SHIT WHEN YOUR DONE
   int billId=0;
   double rent=0;
   double electricity=0;
   double water=0;
   double gas=0;
   double internet=0;
   double total=0;
   QString dateAdded;
   QString dateDue;
   int row = -1;

   foreach(QModelIndex index, indexes){

      row =proxy->mapToSource(index).row();


      QModelIndex billIdIndex = table->index(row, 0, QModelIndex());
      QVariant varBillId = table->data(billIdIndex, Qt::DisplayRole);
      billId = varBillId.toInt();

      QModelIndex rentIndex = table->index(row, 1, QModelIndex());
      QVariant varRent = table->data(rentIndex, Qt::DisplayRole);
      rent = varRent.toDouble();

      QModelIndex electricityIndex = table->index(row, 2, QModelIndex());
      QVariant varElectricity = table->data(electricityIndex, Qt::DisplayRole);
      electricity = varElectricity.toDouble();

      QModelIndex waterIndex = table->index(row, 3, QModelIndex());
      QVariant varWater = table->data(waterIndex, Qt::DisplayRole);
      water= varWater.toDouble();

      QModelIndex gasIndex = table->index(row, 4, QModelIndex());
      QVariant varGas = table->data(gasIndex, Qt::DisplayRole);
      gas = varGas.toDouble();

      QModelIndex internetIndex = table->index(row, 5, QModelIndex());
      QVariant varInternet = table->data(internetIndex, Qt::DisplayRole);
      internet = varInternet.toDouble();

      QModelIndex totalIndex = table->index(row, 6, QModelIndex());
      QVariant varTotal = table->data(totalIndex, Qt::DisplayRole);
      total = varTotal.toDouble();

      QModelIndex dateAddedIndex = table->index(row, 7, QModelIndex());
      QVariant varDateAdded = table->data(dateAddedIndex, Qt::DisplayRole);
      dateAdded = varDateAdded.toString();

      QModelIndex dateDueIndex = table->index(row, 8, QModelIndex());
      QVariant varDateDue= table->data(dateDueIndex, Qt::DisplayRole);
      dateDue = varDateDue.toString();

   }

   //table is only updated if dialog has any changes made to it
   //DO NOT ALLOW CHANGES TO KEY ATTRIBUTES (future)
   add_dialog dialog;
   dialog.setWindowTitle(tr("Edit a Bill"));

   dialog.billIdText->setReadOnly(true);
   dialog.billIdText->setText(QString::number(billId));

   dialog.rentText->setReadOnly(false);
   dialog.rentText->setValue(rent);

   dialog.electricityText->setReadOnly(false);
   dialog.electricityText->setValue(electricity);

   dialog.waterText->setReadOnly(false);
   dialog.waterText->setValue(water);

   dialog.gasText->setReadOnly(false);
   dialog.gasText->setValue(gas);

   dialog.internetText->setReadOnly(false);
   dialog.internetText->setValue(internet);

   dialog.totalText->setReadOnly(true);
   dialog.totalText->setText(QString::number(total));

   dialog.dateAddedText->setReadOnly(true);
   dialog.dateAddedText->setText(dateAdded);

   dialog.dateDueText->setReadOnly(false);
   dialog.dateDueText->setText(dateDue);
    //IF TEXT DOENST WORK PROPERLY THIS IS PROBABLY WHERE IT WENT WRONG
   if(dialog.exec()){

       double newRent = dialog.rentText->value();
       double newElectricity = dialog.electricityText->value();
       double newWater = dialog.waterText->value();
       double newGas = dialog.gasText->value();
       double newInternet = dialog.internetText->value();
       double newTotal = 0; //if editing bill we need to re-add the total
       QString newDateDue = dialog.dateDueText->displayText();


       if(newRent != rent || newElectricity != electricity || newWater !=water ||
          newGas != gas || newInternet != internet || newTotal != total
               || newDateDue != dateDue){ //if any of these attributes changes...

           QModelIndex index = table->index(row, 1, QModelIndex());
           table->setData(index,newRent, Qt::EditRole);

           index = table->index(row, 2, QModelIndex());
           table->setData(index,newElectricity, Qt::EditRole);

           index = table->index(row, 3, QModelIndex());
           table->setData(index, newWater, Qt::EditRole);

           index = table->index(row, 4, QModelIndex());
           table->setData(index,newGas, Qt::EditRole);

           index = table->index(row, 5, QModelIndex());
           table->setData(index,newInternet, Qt::EditRole);

           index = table->index(row, 6, QModelIndex());
           newTotal=newRent+newElectricity+newWater+newGas+newInternet+newTotal;
           table->setData(index,newTotal, Qt::EditRole);

//           index = table->index(row, 7, QModelIndex());
//           table->setData(index,dateAdded, Qt::EditRole);

           index = table->index(row, 8, QModelIndex());
           table->setData(index,newDateDue, Qt::EditRole);

           //allocate the new profit into the map
           totalMap.insert(billId,newTotal);
       }
   }
}

void item_widget::removeEntry()
{
    int billId=0;

    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes){
        int row=proxy->mapToSource(index).row();
        table->removeRows(row, 1, QModelIndex());

        //get itemid
        QModelIndex billIdIndex = table->index(row, 0, QModelIndex());
        QVariant varBillId = table->data(billIdIndex, Qt::DisplayRole);
        billId = varBillId.toInt();
        ++billId; //tbh i dont know why it gives me one lower but whatever
    }

    if (table->rowCount(QModelIndex())==0){
        insertTab(0,newItemTab, "Items");
    }
   totalMap.remove(billId);
}

void item_widget::setupTabs()
{
    //This tab creates the "Everything" tab
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);
    proxyModel->setFilterKeyColumn(0);

    QTableView *tableView = new QTableView;

    tableView->setModel(proxyModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);


    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged, this,
            &item_widget::selectionChanged);
    connect(this, &QTabWidget::currentChanged, this, [this](int tabIndex){
        auto *tableView = qobject_cast<QTableView*>(widget(tabIndex));
        if(tableView)
            emit selectionChanged(tableView->selectionModel()->selection());
    });
    addTab(tableView,"All Bills");
    }


//when u click "open file" it opens that particular file
void item_widget::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, tr("Can't open that file."), file.errorString());
        return;
    }

    //if theres a problem check this closely
    QList<Item> items;
    QDataStream in(&file);
    in >> items;
    if(items.isEmpty()){
        QMessageBox::information(this, tr("There are no items in the file"),
                                 tr("The file you are trying to open has no items in it."));

    }else{

        //necessary because otherwise it gives me items in reverse order
        std::reverse(items.begin(),items.end());

        //"manually" inputs entries from the file so as to avoid many conflicts
        for(const auto &item: qAsConst(items))
            addEntry(item.billId, item.rent, item.electricity, item.water,
                     item.gas,item.internet, item.total,item.dateAdded,item.dateDue);
    }

}

void item_widget::writeToFile(const QString &fileName)
{
    QFile file(fileName);


    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);

    out << table->getItems();
}
