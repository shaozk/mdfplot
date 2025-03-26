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
#include <QMouseEvent>

class SignalListView : public QTableView
{
    Q_OBJECT
public:
    explicit SignalListView(QWidget* parent = nullptr);
    ~SignalListView();  
    
signals:
    void signalSelected(const QString& signalName);

protected:
    // 重写 mousePressEvent 事件处理函数
    void mousePressEvent(QMouseEvent *event) override;
private:

private:
};