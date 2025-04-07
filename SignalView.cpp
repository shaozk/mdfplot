#include "SignalView.h"
#include "Signals.h"

SignalView::SignalView(const QString& filePath, QWidget* parent)
    : QWidget(parent)
{
    // 新建视图
    mExplorer = new SignalExplorer(this);
    mModel = new SignalListModel(this);
    mPlot = new SignalPlot();

    mReader = new SignalReader(filePath);
    auto signalList = mReader->getSignalList();
    for (auto signal : signalList)
    {
        mModel->addSignal(signal);
    }
    mExplorer->setModel(mModel);
    // Plot
    connect(mExplorer, &SignalExplorer::signalSelected, this, &SignalView::plotSignal);
    connect(mExplorer, &SignalExplorer::signalCanceled, this, &SignalView::clearSignal);
    
    // Layout
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mExplorer);
    splitter->addWidget(mPlot);
    QList<int> list;
    list.append(200);
    list.append(600);
    splitter->setSizes(list);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(splitter);

    setLayout(layout);


}

SignalView::~SignalView()
{

}

bool SignalView::loadFile(const QString& filePath)
{
#if 0
    mReader = new SignalReader(filePath);
    // 获取信号里列表
    auto signalList = mReader->getSignalList();

    for (auto signal : signalList)
    {
        //mModel->addSignal(Signals(signal, "test", 1.0));
    }
#endif
    return true;
}

void SignalView::plotSignal(const Signals* signal)
{
    mPlot->removeAllRect();
    auto signalName = signal->name();
    QVector<double> signalLine = mReader->getSignalValueList(signalName);
    mPlot->addSubRect(signal, signalLine);
}

void SignalView::clearSignal()
{
    mPlot->removeAllRect();
}