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
#include <QVector>
#include <QList>

class Signals;
class QCustomPlot;
class QCPAxisRect;
class Signals;

class SignalPlot : public QCustomPlot  
{
public:
    explicit SignalPlot(QWidget *parent = nullptr);
    ~SignalPlot();

    void addSubRect(const Signals* signal, const QVector<double>& valueList);
    void removeAllRect();

private:
    QCPAxisRect* createSubRect(int no);
    void plotSignal(QCPAxisRect* rect, const Signals* signal, const QVector<double>& valueList);

private:
    QList<QCPAxisRect*> mRectList;
    size_t mRectCount;
    
};
 
