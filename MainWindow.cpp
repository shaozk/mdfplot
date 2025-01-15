#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QDebug>

using namespace mdf;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mPlot(new QCustomPlot)
    , mReader(nullptr)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(mPlot);

    on_actionOpenFile_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    // TODO
    // 打开文件管理器，获取文件路径
    QString filePath = "/Users/data/mdf/Recorder_2024-06-17_01-05-29.mf4";
    mReader = new SignalsReader(filePath);

    // 获取信号里列表
    auto signalList = mReader->getSignalList();
    ui->listWidget->addItems(signalList);

    if (signalList.isEmpty())
    {
        return;
    }

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // 获取选中行状态
    auto signalName = item->text();
    qDebug() << signalName;
    auto vec = mReader->getSignalValueList(signalName);
    qDebug() << vec.size();

}

