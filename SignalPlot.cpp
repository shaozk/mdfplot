#include "SignalPlot.h"

#include "Signals.h"
#include <QVector>
#include <QList>
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
    replot();
}

QCPAxisRect* SignalPlot::createSubRect(int no)
{
    QCPAxisRect* rect = new QCPAxisRect(this);

    rect->setAutoMargins(QCP::msRight);
    rect->axis(QCPAxis::atBottom)->setRange(0, 2000);
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
#if 0
    QCPItemStraightLine* line = new QCPItemStraightLine(this);
    line->setClipAxisRect(rect);
    line->setLayer("overlay");
    line->setPen(QPen(Qt::black, 1, Qt::SolidLine));//设置游标线的样式
    line->setClipToAxisRect(true);//自适应范围
    line->setVisible(true);
    QCPRange keyRange = rect->axis(QCPAxis::atBottom)->range();
    line->point1->setCoords(0, keyRange.upper);//起点坐标
    line->point2->setCoords(0, keyRange.lower);//终点坐标
#endif
    return rect;

}