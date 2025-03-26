/**
 * @file SignalView.h
 * @author shaozk (913667678@qq.com)
 * @brief 绘图窗口
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include "SignalListView.h"
#include "SignalListModel.h"
#include "SignalPlot.h"
#include "SignalReader.h"

#include <QWidget>
#include <QString>

class SignalView : public QWidget 
{
    Q_OBJECT
public:
    explicit SignalView(const QString& filePath = "", QWidget* parent = nullptr);
    ~SignalView();

    bool loadFile(const QString& filePath);
    //void addSignal(const Signals& signal);

private:
    SignalListView* mView;
    SignalListModel* mModel;
    SignalPlot* mPlot;

    SignalReader* mReader;
};