/**
 * @file SignalListModel.h
 * @author shaozk (913667678@qq.com)
 * @brief 自定义信号列表模型
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include <QAbstractItemModel>
#include <QList>
#include "Signals.h"

class Signals;


class SignalListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SignalListModel(QObject *parent = nullptr);
    ~SignalListModel() override;

    enum SignalItem
    {
        NameItem = 0,
        ValueItem,
        ColorItem,
        SignalItemCount
    };
#if 1
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
#endif
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
   
    // 自定义方法
    void addSignal(const Signals& signal);
    const Signals* getSignal(const QModelIndex& index);
    // void removeSignal(int row);
    // void updateSignal(int row, const Signals& signal);
    // void addSignalList(SignalList& signalList);

private:

    QVector<Signals> mSignalList;
    
};