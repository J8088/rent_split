#include "tablemodel.h"

/*We implement the two constructors as defined in the header file. The second constructor
initializes the list of contacts in the model, with the parameter value.*/

tablemodel::tablemodel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

tablemodel::tablemodel(QList<Item> items, QObject *parent)
    :QAbstractTableModel (parent), items(items)
{

}

int tablemodel::rowCount(const QModelIndex &parent) const
{
    /*The Q_UNUSED() macro prevents the compiler
     from generating warnings regarding unused parameters. */

    Q_UNUSED(parent);
    return items.size();
}

int tablemodel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    /*
     * this will always return a set number because we wont be adding
     * any columns while the program us running (as of now).
     * THIS WILL CHANGE IN THE FUTURE CHANGE THIS
     * IN THE FUTURE
    */
    return 9;
}

QVariant tablemodel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >=items.size() || index.row() <0)
        return QVariant();
    if(role == Qt::DisplayRole) {
        const auto &item = items.at(index.row());

                switch (index.column()){
                case 0: return item.billId;
                case 1: return item.rent;
                case 2: return item.electricity;
                case 3: return item.water;
                case 4: return item.gas;
                case 5: return item.internet;
                case 6: return item.total;
                case 7: return item.dateAdded;
                case 8: return item.dateDue;
                default: return QVariant();
             }
    }
    return QVariant(); //safety measure
}
//names and orientation of header and tabs
QVariant tablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        /* this switch is decided by ^method above
           typeofitem is 0, colorofitem is 1, etc...*/
        switch (section){

              case 0: return tr("Bill #");
              case 1: return tr("Rent");
              case 2: return tr("Electricity");
              case 3: return tr("Water");
              case 4: return tr("Gas");
              case 5: return tr("Internet");
              case 6: return tr("Total");
              case 7: return tr("Date Added");
              case 8: return tr("Date Due");
              default: return QVariant();

        }
    }
    return QVariant();
}
//called b4 new data is added to properly display information when added
bool tablemodel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    int totalRows=rows;
    //have to do -1 because we count our position twice technically
    beginInsertRows(QModelIndex(), position, (position+rows-1));

    for(int row=0;row < totalRows;++row)
        items.insert(position,{ int(),double(),double(),double(),double(),double(),double(),QString(),QString()});

    endInsertRows();
    return true;

}

bool tablemodel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    int totalRows=rows;
    beginRemoveRows(QModelIndex(),position, (position+rows-1));
    for(int row=0; row < totalRows; ++row)
        items.removeAt(position);

    endRemoveRows();
    return true;
}

bool tablemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        int row = index.row();

        auto item = items.value(row);
        // CHANGE THIS IF YOU PLAN ON ADDING MORE COLUMNS DUMBASS

        switch (index.column()){
        case 0: item.billId = value.toInt();
            break;
        case 1: item.rent = value.toDouble();
            break;
        case 2: item.electricity = value.toDouble();
            break;
        case 3: item.water = value.toDouble();
            break;
        case 4: item.gas = value.toDouble();
            break;
        case 5: item.internet = value.toDouble();
            break;
        case 6: item.total = value.toDouble();
            break;
        case 7: item.dateAdded = value.toString();
            break;
        case 8:item.dateDue= value.toString();
            break;
        default: return false;
        }
        items.replace(row,item);
        emit dataChanged(index,index,{role});

        return true;
        }

        return false;

}

Qt::ItemFlags tablemodel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<Item> tablemodel::getItems() const
{
    return items;
}
