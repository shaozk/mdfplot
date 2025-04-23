/**
 * @file SignalView.h
 * @author shaozk (913667678@qq.com)
 * @brief 绘图窗口
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) shaozk
 * 
 */

#pragma once

#include "SignalExplorer.h"
#include "SignalListModel.h"
#include "SignalPlot.h"
#include "SignalReader.h"

#include <QWidget>

#if 0
class QString;

using ChannelObserverListPtr = std::unique_ptr<ChannelObserverList>;

class SignalView : public QWidget 
{
    Q_OBJECT
public:
    explicit SignalView(const QString& filePath = "", QWidget* parent = nullptr);
    ~SignalView();

    bool loadFile(const QString& filePath);
    //void addSignal(const Signals& signal);

private slots:
    void plotSignal(const Signals* signal);
    void clearSignal();

private:
    SignalExplorer* mExplorer;
    SignalListModel* mModel;
    SignalPlot* mPlot;

    SignalReader* mReader;
};

#else

#define MAX_SHOW_SIGNAL_NUM 20

class SignalView : public QWidget
{
    Q_OBJECT
private:

    /**
     * @brief 初始化成员变量
    */
    void initData();

    /**
     * @brief 初始化信号表格
    */
    void initTable();

    /**
     * @brief 初始化信号图
    */
    void initPlot();

    /**
     * @brief 初始化游标
    */
    void initCursor();

    /**
     * @brief 显示信号表格
    */
    void showTable();

    /**
     * @brief 显示信号图
    */
    void showPlot();

    /**
     * @brief 显示游标
    */
    void showCursor();

    /**
     * @brief 更新表格数据
     * @param frame 帧
    */
    void updateTable(size_t frame);

    /**
     * @brief Stub
     * @param frame 帧 
    */
    void updatePlot(size_t frame);

    /**
     * @brief 更新游标位置
     * @param frame 帧
    */
    void updateCursor(size_t frame);

    void CreateQCPAxisRect(int axisNum);
    void RemoveQCPAxisRectAll();
    void connectAllxAsix(bool on);
    void autoAdjustTableItemWidth();


public:
    explicit SignalView(const QString& filePath, QWidget* parent = nullptr);
    ~SignalView();

    /**
     * @brief 添加信号
     * @param name 信号名
     * @param color 信号颜色
     * @param signal 信号数据（数组）
    */
    void addSignal(const QString& name, const QColor& color, const QVector<double>& signal);

    /**
     * @brief 信号数据显示
    */
    void showSignal();

    /**
     * @brief 更新游标位置
     * @param frameId 帧数（游标位置）
    */
    void update(size_t frameId);


    /**
     * @brief 清空信号
    */
    void clear();

private slots:

    void onTableSelected(const QModelIndex& index);
    void onMousePress(QMouseEvent* event);
    void onMouseMove(QMouseEvent* event);
    void onMouseRelease(QMouseEvent* event);

    void onSelectionChanged();

signals:
    void frameChanged(size_t frame);

private:

    QTableView* mTableView;
    QCustomPlot* mSignalPlot;              ///< 信号图
    QVector<QCPAxisRect*> mAxisList;       ///< 子坐标系
    QVector<QCPItemStraightLine*> mCursorList;      ///< 信号图游标
    bool mCursorSelectFlag;                ///< 信号游标鼠标选中标志

    size_t mFrameId;                       ///< 当前帧
    size_t mTotalSignal;                   ///< 信号数
    size_t mSelectSignal;
    size_t mTotalFrame;                    ///< 总帧数
    QVector<bool>* mCheckVec;
    QVector<QString>* mNameVec;            ///< 信号名列表 
    QVector<QColor>* mColorVec;            ///< 颜色名列表
    QVector<QVector<double>>* mSignalVec;   ///< 信号数据列表

    QStandardItemModel* mTableModel;

    SignalReader* mReader;
};


#endif
