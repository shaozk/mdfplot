/**
 * @file SignalPlot.h
 * @author shaozk (913667678@qq.com)
 * @brief 信号曲线绘图
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include "qcp/qcustomplot.h"
#include "Signals.h"

#include <QVector>
#include <QList>

class SignalPlot : public QCustomPlot  
{
public:
    explicit SignalPlot(QWidget *parent = nullptr);
    ~SignalPlot();

    void addSubRect(const QString& signalName);
    void removeAllRect();
    void createSubRect(int num);

    void plotSignal(QCPAxisRect* rect, const QString& sigName, QColor color, const QVector<float>& signal);

private:
    QList<QCPAxisRect*> mRectList;
    
};
 
