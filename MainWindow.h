/**
 * @file        MainWindow.h
 * @author      shaozk
 * @date        2025/01/10
 * @brief       主界面文件
 * @details
 */

#pragma

#include <QMainWindow>

#include "qcp/qcustomplot.h"
#include "SignalsReader.h"


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

private slots:
    void on_actionOpenFile_triggered();
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QCustomPlot* mPlot;

    SignalsReader* mReader;
};

