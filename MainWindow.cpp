#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QDebug>

#include "SignalsReader.h"

using namespace mdf;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mPlot(new QCustomPlot)
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
    SignalsReader reader(filePath);
    auto dgList = reader.getDataGroupList();
    for (auto* dg4 : dgList)
    {
        qDebug() << dg4->Description();
        auto chGroup = dg4->ChannelGroups();
        for (auto* group : chGroup)
        {
            qDebug() << group->Name();
        }
    }

    // 获取信号里列表
    auto subscriberList = reader.getChannelObserverList();
    QStringList labelList;
    for (auto& sub : subscriberList)
    {
        qDebug() << sub->Name();
        labelList.emplace_back(QString::fromStdString(sub->Name()));
    }
    ui->listWidget->addItems(labelList);


}

