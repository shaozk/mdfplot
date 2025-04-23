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
class QCPItemStraightLine;
class Signals;
class MouseEvent;

class SignalPlot : public QCustomPlot  
{
    Q_OBJECT
public:
    explicit SignalPlot(QWidget *parent = nullptr);
    ~SignalPlot();

    void addSubRect(const Signals* signal, const QVector<double>& valueList);
    void removeAllRect();

signals:
    void cursorChanged(int pos);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QCPAxisRect* createSubRect(int no);
    void plotSignal(QCPAxisRect* rect, const Signals* signal, const QVector<double>& valueList);

private:
    QCPAxisRect* mRect;
    QCPItemStraightLine* mCursor;
    size_t mRectCount;
    
};
 
