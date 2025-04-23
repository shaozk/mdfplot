#include "SignalListModel.h"
#include "Signals.h"

#include <QString>
#include <QDebug>
#include <utility>

SignalListModel::SignalListModel(QObject* parent)
    : QAbstractListModel(parent)
{

}

SignalListModel::~SignalListModel()
{
    
}

QModelIndex SignalListModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex SignalListModel::parent(const QModelIndex& index) const
{
    return QModelIndex();
}

int SignalListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())  
    {
        return 0;
    }
    return mSignalList.size();
}

int SignalListModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return SignalItemCount;
}

QVariant SignalListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QString("Name");
            break;
        case 1:
            return QString("Value");
            break;
        case 2:
            return QString("Color");
            break;
        default:
            break;
        }
    }
    return QVariant();
}


QVariant SignalListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= mSignalList.size(), role != Qt::DisplayRole)
    {
        return QVariant();
    }

    const auto& signal = mSignalList.at(index.row());

    switch (index.column())
    {
    case 0:
        return signal.name();   
        break;
    case 1:
        return signal.value();
        break;
    case 2:
        return signal.color();
        break;
    default:
        return "Valid";
        break;
    }
    return QVariant();

}

QHash<int, QByteArray> SignalListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "Name";
    roles[1] = "Value";
    roles[2] = "Color";
    return roles;
}

void SignalListModel::addSignal(const Signals& signal)
{
    beginInsertRows(QModelIndex(), mSignalList.size(), mSignalList.size());
    mSignalList.append(signal);
    endInsertRows();
}

const Signals* SignalListModel::getSignal(const QModelIndex& index)
{
    if (index.isValid() && index.row() < mSignalList.size())
    {
        return &mSignalList[index.row()];
    }
    return nullptr;
}