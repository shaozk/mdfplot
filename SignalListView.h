/**
 * @file SignalListView.h
 * @author shaozk (913667678@qq.com)
 * @brief 信号列表视图
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include "SignalListModel.h"

#include <QWidget>
#include <QTableView>
#include <QListView>
#include <QListWidgetItem>

class SignalListView : public QWidget
{
    Q_OBJECT
public:
    explicit SignalListView(QWidget* parent = nullptr);
    ~SignalListView();    

    void setModel(SignalListModel* model) { mView->setModel(model); }

private:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    QTableView* mView;    
};