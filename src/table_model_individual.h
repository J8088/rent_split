#ifndef TABLE_MODEL_INDIVIDUAL_H
#define TABLE_MODEL_INDIVIDUAL_H

#include <QAbstractTableModel>
#include <QList>

struct People
{
   //PP== per person
    int billId;
    double rentTotalPP;
    double utilitiesTotalPP;
    double totalOwedPP;
    int extraRentCents;
    int extraUtilityCents;

    bool operator==(const People &other) const
    {
        return billId == other.billId && rentTotalPP == other.rentTotalPP &&
                utilitiesTotalPP == other.utilitiesTotalPP &&
                totalOwedPP == other.totalOwedPP && extraRentCents == other.extraRentCents
                && extraUtilityCents == other.extraUtilityCents;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const People &people)
{
    return stream <<people.billId << people.rentTotalPP << people.utilitiesTotalPP
                  << people.totalOwedPP << people.extraRentCents
                  << people.extraUtilityCents;
}

inline QDataStream &operator>>(QDataStream &stream, People &people)
{
    return stream >> people.billId >> people.rentTotalPP >> people.utilitiesTotalPP
                  >> people.totalOwedPP >> people.extraRentCents
                  >> people.extraUtilityCents;
}

class table_model_individual : public QAbstractTableModel
{
    Q_OBJECT
public:
    table_model_individual(QObject *parent = 0);
    table_model_individual(QList<People> people, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData (int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<People> getPeople() const;

private:
    QList<People> people;
};

#endif // TABLE_MODEL_INDIVIDUAL_H
