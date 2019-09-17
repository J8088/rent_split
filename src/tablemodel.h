#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

struct Item
{
    int billId;
    double rent;
    double electricity;
    double water;
    double gas;
    double internet;
    double total;
    QString dateAdded;
    QString dateDue;

    bool operator==(const Item &other) const
    {
        return billId == other.billId && rent == other.rent && electricity == other.electricity
               && water == other.water && gas == other.gas
               && internet == other.internet && total == other.total
               && dateAdded == other.dateAdded&& dateDue== other.dateDue;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Item &item)
{
    return stream <<item.billId << item.rent << item.electricity
                  << item.water << item.gas << item.internet
                  << item.total << item.dateAdded << item.dateDue;
}

inline QDataStream &operator>>(QDataStream &stream, Item &item)
{
    return stream >> item.billId >> item.rent >> item.electricity
                  >> item.water >> item.gas >> item.internet
                  >> item.total >> item.dateAdded >> item.dateDue;
}

//one colon denotes inheritance- tablemodel inherits from QAbstractTableModel
class tablemodel : public QAbstractTableModel
{
    Q_OBJECT
public:
    tablemodel(QObject *parent = 0);
    tablemodel(QList<Item> items, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData (int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Item> getItems() const;

private:
    QList<Item> items;
};

#endif // TABLEMODEL_H
