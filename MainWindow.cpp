#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "SignalView.h"
#include "Globals.h"
#include "About.h"

#include <QDebug>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(Globals::name() + " " + Globals::versionString());

    // 在主窗口中创建 MDI 区域
    mMdiArea = new QMdiArea(this);
    setCentralWidget(mMdiArea);
    mMdiArea->setViewMode(QMdiArea::TabbedView);
    mMdiArea->setTabsClosable(true);
    mMdiArea->setTabsMovable(true);
    //on_actionOpenFile_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenFile_triggered()
{
    // 打开文件管理器，获取文件路径
    QString filePath = "U:\\mdf\\Recorder_2024-06-17_01-05-29.mf4";
    SignalView *view = new SignalView(filePath);

    QMdiSubWindow* subWindow = mMdiArea->addSubWindow(view);
    subWindow->setWindowTitle(filePath);
    mMdiArea->addSubWindow(subWindow);
    subWindow->show();

}

void MainWindow::on_actionAbout_triggered()
{
    About* about = new About(this);
    about->exec();
}