#include "SignalView.h"

SignalView::SignalView(const QString& filePath, QWidget* parent)
    : QWidget(parent)
{
    
    // 新建视图
    mView = new SignalListView();
    mModel = new SignalListModel();
    mPlot = new SignalPlot();

    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mView->setModel(mModel);


    // Plot


    connect(mView, &SignalListView::signalSelected, mPlot, &SignalPlot::addSubRect);
    

    // Layout
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mView);
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