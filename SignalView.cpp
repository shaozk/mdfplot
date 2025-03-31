#include "SignalView.h"

SignalView::SignalView(const QString& filePath, QWidget* parent)
    : QWidget(parent)
{
    
    // 新建视图
    mExplorer = new SignalExplorer();
    mModel = new SignalListModel();
    mPlot = new SignalPlot();

    SignalReader reader(filePath);
    auto signalList = reader.getSignalList();
    for (auto signal : signalList)
    {
        mModel->addSignal(Signals(signal, "test", 1.0));
    }
    mExplorer->setModel(mModel);
    // C++ 版本
    // Plot
    // connect(mView, &SignalListView::signalSelected, mPlot, &SignalPlot::addSubRect);
    

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

    mReader = new SignalReader(filePath);
    // 获取信号里列表
    auto signalList = mReader->getSignalList();

    for (auto signal : signalList)
    {
        mModel->addSignal(Signals(signal, "test", 1.0));
    }
    return true;
}