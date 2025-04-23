/**
 * @file SignalExplorer.h
 * @author shaozk (913667678@qq.com)
 * @brief 信号列表视图
 * @version 0.1
 * @date 2025-03-23
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include <QWidget>

class Signals;
class SignalListModel;

class QListView;
class QTreeView;
class QLineEdit;
class QPushButton;
class QFrame;
class QMouseEvent;

class SignalExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit SignalExplorer(QWidget* parent = nullptr);
    ~SignalExplorer();  

    void setModel(SignalListModel* model);
    
signals:
    void signalCanceled();
    void signalSelected(const Signals* signal);

public slots:
    void valueChanged(int pos);

protected:
    void signalClicked(const QModelIndex& index);

private:
    QTreeView* mSignalView;

    QLineEdit* mSearchEdit{nullptr};
    QFrame* mSearchFrame{nullptr};
	QPushButton* mSearchBtn{nullptr};
	QPushButton* mCancelBtn{nullptr};
};