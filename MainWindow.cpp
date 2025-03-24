#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "SignalListModel.h"

#include <QDebug>
#include <QList>

using namespace mdf;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mPlot(new QCustomPlot)
    , mReader(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("MdfPlot");

    //on_actionOpenFile_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    // 新建视图
    mListView = new SignalListView(this);
    mModel = new SignalListModel();
    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mModel->addSignal(Signals("test", "test", 1.0));
    mListView->setModel(mModel);
    

    QWidget* centralWidget = new QWidget();
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mListView);
    splitter->addWidget(mPlot);
    QList<int> list;
    list.append(200);
    list.append(600);
    splitter->setSizes(list);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(splitter);

    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);   

#if 0
    // 打开文件管理器，获取文件路径
    QString filePath = "U:\\mdf\\Recorder_2024-06-17_01-05-29.mf4";
    mReader = new SignalReader(filePath);

    // 获取信号里列表
    auto signalList = mReader->getSignalList();

    for (auto signal : signalList)
    {
        mModel->addSignal(Signals(signal, "test", 1.0));
    }
#endif
}

