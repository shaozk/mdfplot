#include "SignalPlot.h"

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

void SignalPlot::addSubRect(const QString& signalName)
{
    qDebug() << "add sub rect " << signalName;
    removeAllRect();
    createSubRect(1);
    replot();
}

void SignalPlot::plotSignal(QCPAxisRect* rect, const QString& sigName, QColor color, const QVector<float>& signal)
{
    QVector<double> vecPointX;
    QVector<double> vecPointY;

    for (auto iFrame = 0; iFrame < signal.size(); ++iFrame)
    {
        vecPointX.append(iFrame);
        vecPointY.append(signal[iFrame]);
    }
    
    QCPGraph* graph = new QCPGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
    graph->setName(sigName);
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
    mRectList.clear();
    plotLayout()->simplify();
}


void SignalPlot::createSubRect(int num)
{
    for (int i = 0; i < num; i++) {

        QCPAxisRect* rect = new QCPAxisRect(this);

        rect->setAutoMargins(QCP::msRight);
        rect->axis(QCPAxis::atBottom)->setRange(0, 2000);
        rect->axis(QCPAxis::atBottom)->grid()->setVisible(false);
        rect->axis(QCPAxis::atLeft)->grid()->setVisible(false);
        rect->setRangeDrag(Qt::Horizontal | Qt::Vertical); //水平方向拖动
        rect->setRangeZoom(Qt::Horizontal | Qt::Vertical); //水平方向缩放
        rect->setMargins(QMargins(50, 0, 0, 0));

        if (i == num - 1)
        {
            rect->axis(QCPAxis::atBottom)->setTicks(true);
        }
        else
        {
            rect->axis(QCPAxis::atBottom)->setTicks(false);
        }

        if (!plotLayout()->hasElement(i, 0))
        {
            plotLayout()->addElement(i, 0, rect);
        }
        
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

    }
    //connectAllxAsix(true);

}