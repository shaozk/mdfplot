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

#include "Signals.h"

#include <QObject>
#include <QAbstractItemModel>
#include <QList>

class SignalListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SignalListModel(QObject *parent = nullptr);
    ~SignalListModel() override;

    enum ColoumnType{
        Name = 0,
        Value,
        Color,
        CololumnCount
    };
    Q_ENUM(ColoumnType)

#if 1
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
#endif
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    
    void addSignal(const Signals& signal);
    void setSignalList(const QList<Signals>& signalList);

private:

    QList<Signals> mSignalList;


};