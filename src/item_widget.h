/*This is technically the main class involved as it provides
 *   functions to add, edit and remove contacts,
 *  to save the contacts to a file and to load them from a file.*/

#ifndef ITEM_WIDGET_H
#define ITEM_WIDGET_H

#include "newitemtab.h"
#include "tablemodel.h"
#include "table_model_individual.h"

#include <QItemSelection>
#include <QTableWidget>
#include <QMap>
QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
QT_END_NAMESPACE

class item_widget : public QTabWidget
{
    Q_OBJECT

public:
    item_widget(QWidget *parent = 0);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);

public slots:
    void showAddEntryDialog();
    void addEntry(int billId,double rent, double electricity,double water, double gas,double internet,
                  double total, QString dateAdded, QString dateDue);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupTabs();
    void peopleTabAdd(int billId,double rent, double electricity,double water,
                      double gas,double internet, int row);
    tablemodel *billTable;
    table_model_individual *peopleTable;
    newitemtab *newItemTab;
    QSortFilterProxyModel *proxyModel;
};

#endif // ITEM_WIDGET_H
