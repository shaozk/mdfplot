#include "SignalListModel.h"

#include <QString>

SignalListModel::SignalListModel(QObject* parent)
    : QAbstractItemModel(parent)
{
}

SignalListModel::~SignalListModel()
{
}

#if 1
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
#endif

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
    return CololumnCount;
}

QVariant SignalListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case SignalListModel::Name:
            return QString("Name");
            break;
        case SignalListModel::Value:
            return QString("Value");
            break;
        case SignalListModel::Color:
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

    auto type = static_cast<ColoumnType>(index.column());
    switch (type)
    {
    case SignalListModel::Name:
        return signal.name();   
        break;
    case SignalListModel::Value:
        return signal.value();
        break;
    case SignalListModel::Color:
        return signal.color();
        break;
    default:
        break;
    }
    return QVariant();

}

QHash<int, QByteArray> SignalListModel::roleNames() const
{
    return {};
}

void SignalListModel::addSignal(const Signals& signal)
{
    beginInsertRows(QModelIndex(), mSignalList.size(), mSignalList.size());
    mSignalList.append(signal);
    endInsertRows();
}

void SignalListModel::setSignalList(const QList<Signals>& signalList)
{
    beginResetModel();
    mSignalList = signalList;
    endResetModel();
}