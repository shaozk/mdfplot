/**
 * @file        MainWindow.h
 * @author      shaozk
 * @date        2025/01/10
 * @brief       主界面文件
 * @details
 */

#pragma once

#include <QMainWindow>

#include "qcp/qcustomplot.h"
#include "SignalReader.h"
#include "SignalListView.h"
#include "SignalListModel.h"

#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_actionOpenFile_triggered();


private:
    Ui::MainWindow *ui;
    QCustomPlot* mPlot;
    SignalListView* mListView;

    SignalReader* mReader;

    //QStandardItemModel* mModel;
    SignalListModel* mModel;
};

