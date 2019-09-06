#include "table_model_individual.h"

table_model_individual::table_model_individual(QObject *parent)
    :QAbstractTableModel(parent)
{

}

table_model_individual::table_model_individual(QList<People> people, QObject *parent)
    :QAbstractTableModel (parent), people(people)
{

}

int table_model_individual::rowCount(const QModelIndex &parent) const
{
    /*The Q_UNUSED() macro prevents the compiler
     from generating warnings regarding unused parameters. */

    Q_UNUSED(parent);
    return people.size();
}

int table_model_individual::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    /*
     * this will always return a set number because we wont be adding
     * any columns while the program us running (as of now).
     * THIS WILL CHANGE IN THE FUTURE CHANGE THIS
     * IN THE FUTURE
    */
    return 6;
}

QVariant table_model_individual::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >=people.size() || index.row() <0)
        return QVariant();
    if(role == Qt::DisplayRole) {
        const auto &item = people.at(index.row());

                switch (index.column()){
                case 0: return item.billId;
                case 1: return item.apurvaOwed;
                case 2: return item.edwardOwed;
                case 3: return item.ericOwed;
                case 4: return item.joseOwed;
                case 5: return item.totalOwed;
                default: return QVariant();
             }
    }
    return QVariant(); //safety measure
}

QVariant table_model_individual::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal){
        /* this switch is decided by ^method above
           typeofitem is 0, colorofitem is 1, etc...*/
        switch (section){

              case 0: return tr("Bill #");
              case 1: return tr("What You Owe Apurva");
              case 2: return tr("What You Owe Edward");
              case 3: return tr("What You Owe Eric");
              case 4: return tr("What You Owe Jose");
              case 5: return tr("Total Owed");
              default: return QVariant();

        }
    }
    return QVariant();
}

bool table_model_individual::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    int totalRows=rows;
    //have to do -1 because we count our position twice technically
    beginInsertRows(QModelIndex(), position, (position+rows-1));

    for(int row=0;row < totalRows;++row)
        people.insert(position,{ int(),double(),double(),double(),double(),double()});

    endInsertRows();
    return true;

}

bool table_model_individual::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    int totalRows=rows;
    beginRemoveRows(QModelIndex(),position, (position+rows-1));
    for(int row=0; row < totalRows; ++row)
        people.removeAt(position);

    endRemoveRows();
    return true;
}

bool table_model_individual::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole){
        int row = index.row();

        auto peoples = people.value(row);
        // CHANGE THIS IF YOU PLAN ON ADDING MORE COLUMNS DUMBASS

        switch (index.column()){
        case 0: peoples.billId = value.toInt();
            break;
        case 1: peoples.apurvaOwed = value.toDouble();
            break;
        case 2: peoples.edwardOwed = value.toDouble();
            break;
        case 3: peoples.ericOwed = value.toDouble();
            break;
        case 4: peoples.joseOwed = value.toDouble();
            break;
        case 5: peoples.totalOwed = value.toDouble();
            break;
        default: return false;
        }
        people.replace(row,peoples);
        emit dataChanged(index,index,{role});

        return true;
        }

        return false;

}

Qt::ItemFlags table_model_individual::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<People> table_model_individual::getPeople() const
{
    return people;
}

