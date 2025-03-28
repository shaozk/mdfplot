/**
 * @file        MainWindow.h
 * @author      shaozk
 * @date        2025/01/10
 * @brief       主界面
 * @details
 */

#pragma once

#include <QMainWindow>

#include <QStandardItemModel>
#include <QMdiArea>

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
    void on_actionAbout_triggered();


private:
    Ui::MainWindow *ui;

    // SignalView* mView;
    QMdiArea *mMdiArea;

};

