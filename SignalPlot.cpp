#include "SignalPlot.h"

#include "Signals.h"
#include <QVector>
#include <QList>
#include <QtMath>
SignalPlot::SignalPlot(QWidget* parent)
    : QCustomPlot(parent)
{
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    setSelectionRectMode(QCP::SelectionRectMode::srmNone);//模式：框选放大
    plotLayout()->clear();   // 首先清空默认的轴矩形，让我们从头开始
    plotLayout()->setMargins(QMargins(0, 20, 0, 20));

}

SignalPlot::~SignalPlot()
{
}

void SignalPlot::addSubRect(const Signals* signal, const QVector<double>& valueList)
{
    qDebug() << "add sub rect " << signal->name();
    auto* rect = createSubRect(0);
    plotSignal(rect, signal, valueList);    

    mCursor = new QCPItemStraightLine(this);
    mCursor->setClipAxisRect(rect);
    mCursor->setLayer("overlay");
    mCursor->setPen(QPen(Qt::black, 1, Qt::SolidLine));//设置游标线的样式
    mCursor->setClipToAxisRect(true);//自适应范围
    mCursor->setVisible(true);
    QCPRange keyRange = rect->axis(QCPAxis::atBottom)->range();
    mCursor->point1->setCoords(0, keyRange.upper);//起点坐标
    mCursor->point2->setCoords(0, keyRange.lower);//终点坐标
    replot();
}

void SignalPlot::mousePressEvent(QMouseEvent* event)
{
    QCustomPlot::mousePressEvent(event);
#if 1
    if (event->button() != Qt::LeftButton)
    {
        return;
    }
    QCPAxisRect* rect = axisRectAt(event->pos());
    if (!rect)
    {
        return;
    }

    double posX = qRound(rect->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x()));
    if (posX < 0)
    {
        posX = 0;
    }
    
    QCPRange range = rect->axis(QCPAxis::atBottom)->range();
    mCursor->point1->setCoords(posX, range.upper);
    mCursor->point2->setCoords(posX, range.lower);
#endif 
}

void SignalPlot::mouseMoveEvent(QMouseEvent* event)
{
    QCustomPlot::mouseMoveEvent(event);
}

void SignalPlot::mouseReleaseEvent(QMouseEvent* event)
{
    QCustomPlot::mouseReleaseEvent(event); 
    QCPAxisRect* rect = axisRectAt(event->pos());
    if (!rect)
    {
        return;
    }
    int posX = qRound(rect->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x()));
    emit cursorChanged(posX);
    replot();
}

void SignalPlot::plotSignal(QCPAxisRect* rect, const Signals* signal, const QVector<double>& valueList)
{
    QVector<double> vecPointX;
    QVector<double> vecPointY;

    auto name = signal->name();
    auto color = signal->color(); 

    qDebug() << valueList.size();

    for (auto i = 0; i < valueList.size(); ++i)
    {
        vecPointX.append(i);
        vecPointY.append(valueList[i]);
    }
    
    QCPGraph* graph = new QCPGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
    graph->setName(name);
    graph->setPen(QPen(color, 1));
    graph->setAntialiased(false);
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 2));
    graph->setAdaptiveSampling(true);
    graph->setData(vecPointX, vecPointY, true);
    graph->setVisible(true);
    graph->rescaleAxes(true);

}

void SignalPlot::removeAllRect()
{
    // 移除并删除所有轴矩形
    QList<QCPAxisRect*> rects = axisRects();
    foreach (QCPAxisRect* rect, rects) 
    {
        plotLayout()->remove(rect);
    }    
    clearPlottables();
    replot();
}

QCPAxisRect* SignalPlot::createSubRect(int no)
{
    QCPAxisRect* rect = new QCPAxisRect(this);

    rect->setAutoMargins(QCP::msRight);
    rect->axis(QCPAxis::atBottom)->grid()->setVisible(false);
    rect->axis(QCPAxis::atLeft)->grid()->setVisible(false);
    rect->setRangeDrag(Qt::Horizontal | Qt::Vertical); //水平方向拖动
    rect->setRangeZoom(Qt::Horizontal | Qt::Vertical); //水平方向缩放
    rect->setMargins(QMargins(50, 0, 0, 0));

    if (0 == no)
    {
        rect->axis(QCPAxis::atBottom)->setTicks(true);
    }
    else
    {
        rect->axis(QCPAxis::atBottom)->setTicks(false);
    }

    if (!plotLayout()->hasElement(no, 0))
    {
        plotLayout()->addElement(no, 0, rect);
    }
    //connectAllxAsix(true);

    return rect;
}