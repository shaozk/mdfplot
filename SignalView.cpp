#include "SignalView.h"
#include "Signals.h"
#include "Globals.h"
#if 0
SignalView::SignalView(const QString& filePath, QWidget* parent)
    : QWidget(parent)
{
    // 新建视图
    mExplorer = new SignalExplorer(this);
    mModel = new SignalListModel(this);
    mPlot = new SignalPlot();

    mReader = new SignalReader(filePath);
    auto signalList = mReader->getSignalList();
    for (auto signal : signalList)
    {
        mModel->addSignal(signal);
    }
    mExplorer->setModel(mModel);
    // Plot
    connect(mExplorer, &SignalExplorer::signalSelected, this, &SignalView::plotSignal);
    connect(mExplorer, &SignalExplorer::signalCanceled, this, &SignalView::clearSignal);
    connect(mPlot, &SignalPlot::cursorChanged, mExplorer, &SignalExplorer::valueChanged);
    
    // Layout
    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mExplorer);
    splitter->addWidget(mPlot);
    QList<int> list;
    list.append(200);
    list.append(800);
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
#if 0
    mReader = new SignalReader(filePath);
    // 获取信号里列表
    auto signalList = mReader->getSignalList();

    for (auto signal : signalList)
    {
        //mModel->addSignal(Signals(signal, "test", 1.0));
    }
#endif
    return true;
}

void SignalView::plotSignal(const Signals* signal)
{
    mPlot->removeAllRect();
    auto signalName = signal->name();
    QVector<double> signalLine = mReader->getSignalValueList(signalName);
    mPlot->addSubRect(signal, signalLine);
}

void SignalView::clearSignal()
{
    mPlot->removeAllRect();
}

#else


SignalView::SignalView(const QString& filePath, QWidget* parent)
    : QWidget(parent)
{

    //设置窗口顶置: 一直在最前面
    this->setWindowFlags(Qt::WindowStaysOnTopHint);  // this可以省略

    mTableView = new QTableView();
	mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	mTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mSignalPlot = new QCustomPlot();

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(mTableView);
    splitter->addWidget(mSignalPlot);
    QList<int> list;
    list.append(200);
    list.append(600);
    splitter->setSizes(list);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(splitter);

    //autoAdjustTableItemWidth();

    setAcceptDrops(true);     // 设置主界面接收拖动进来的文件


    initData();

    initTable();
    initPlot();
    initCursor();

    connect(mSignalPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onMousePress(QMouseEvent*)));
    connect(mSignalPlot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(onMouseMove(QMouseEvent*)));
    connect(mSignalPlot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseRelease(QMouseEvent*)));
    connect(mSignalPlot, SIGNAL(selectionChangedByUser()), this, SLOT(onSelectionChanged()));

    connect(mTableView, &QTableView::clicked, this, &SignalView::onTableSelected);

    mReader = new SignalReader(filePath);
    auto signalList = mReader->getSignalList();
    qDebug() << signalList.size();
    for (auto signal : signalList)
    {
        QVector<double> valueList = mReader->getSignalValueList(signal.name());
        addSignal(signal.name(), signal.color(), valueList);
        qDebug() << signal.name() << " " << valueList.size();
    }
    showSignal();
}

void SignalView::autoAdjustTableItemWidth()
{
    // 设置水平滚动条策略为按需显示
    mTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // 获取水平表头
    QHeaderView* hHeaderView = mTableView->horizontalHeader();
    // 设置列的调整模式为根据内容自动调整大小
    mSelectSignal = 0;
    mTotalSignal = 0;
    mCursorSelectFlag = false;
    if (!mCheckVec->isEmpty())
    {
        mCheckVec->clear();
    }
    if (!mNameVec->isEmpty())
    {
        mNameVec->clear();
    }
    if (!mColorVec->isEmpty())
    {
        mColorVec->clear();
    }
    if (!mSignalVec->isEmpty())
    {
        mSignalVec->clear();
    }
    if (mTableModel)
    {
        mTableModel->removeRows(0, mTableModel->rowCount());
    }
}

void SignalView::showSignal()
{
    showTable();
    showPlot();
    showCursor();
}

void SignalView::update(size_t frameId)
{
    if (frameId < mTotalFrame)
    {
        updateCursor(frameId);
        updateTable(frameId);
    }
}

void SignalView::initData()
{
    mFrameId = 0;
    mTotalFrame = 0;
    mSelectSignal = 0;
    mTotalSignal = 0;
    mCursorSelectFlag = false;
    mCheckVec = new QVector<bool>();
    mNameVec = new QVector<QString>();
    mColorVec = new QVector<QColor>();
    mSignalVec = new QVector<QVector<double>>();
}


void SignalView::initTable()
{
    mTableModel = new QStandardItemModel();

    mTableView->setModel((mTableModel));

    // 设置可选多行
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 设置表头
    mTableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("signal")));
    mTableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("color")));
    mTableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("value")));
    
}

SignalView::~SignalView()
{
}


void SignalView::addSignal(const QString& name, const QColor& color, const QVector<double>& signal)
{
    ++mTotalSignal;
    ++mSelectSignal;
    mTotalFrame = signal.size();
    mCheckVec->push_back(true);
    mNameVec->push_back(name);
    mColorVec->push_back(color);
    mSignalVec->push_back(signal);
}


void SignalView::clear()
{
    mFrameId = 0;
    mTotalFrame = 0;
    mTableModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("signal")));
    mTableModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("")));
    mTableModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("value")));

}


void SignalView::connectAllxAsix(bool on)
{
    for (int i = 0; i < mAxisList.count(); ++i) {
        if (on) {
            connect(mSignalPlot->axisRect()->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), mAxisList.at(i)->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
            connect(mAxisList.at(i)->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), mSignalPlot->axisRect()->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
        }
        else
        {
            disconnect(mSignalPlot->axisRect()->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), mAxisList.at(i)->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
            disconnect(mAxisList.at(i)->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), mSignalPlot->axisRect()->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
        }
    }
}


void SignalView::RemoveQCPAxisRectAll()
{
    mSignalPlot->clearGraphs();
    for (int i = 0; i < mAxisList.count(); i++)
    {
        mSignalPlot->plotLayout()->remove(mAxisList.at(i));
        QCPAxisRect* rect = mAxisList.at(i);
        rect = nullptr;
    }
    mAxisList.clear();
    mCursorList.clear();

    mSignalPlot->plotLayout()->simplify();
}


void SignalView::CreateQCPAxisRect(int axisNum)
{
    mAxisList = QVector<QCPAxisRect*>();
    mCursorList = QVector<QCPItemStraightLine*>();
    mSignalPlot->plotLayout()->setMargins(QMargins(0, 20, 0, 20));

    for (int i = 0; i < axisNum; i++) {

        QCPAxisRect* rect = new QCPAxisRect(mSignalPlot);

        rect->setAutoMargins(QCP::msRight);
        rect->axis(QCPAxis::atBottom)->setRange(0, 2000);
        rect->axis(QCPAxis::atBottom)->grid()->setVisible(false);
        rect->axis(QCPAxis::atLeft)->grid()->setVisible(false);
        rect->setRangeDrag(Qt::Horizontal | Qt::Vertical); //水平方向拖动
        rect->setRangeZoom(Qt::Horizontal | Qt::Vertical); //水平方向缩放
        rect->setMargins(QMargins(50, 0, 0, 0));

        if (i == axisNum - 1)
        {
            rect->axis(QCPAxis::atBottom)->setTicks(true);
        }
        else
        {
            rect->axis(QCPAxis::atBottom)->setTicks(false);
        }

        if (!mSignalPlot->plotLayout()->hasElement(i, 0))
        {
            mSignalPlot->plotLayout()->addElement(i, 0, rect);
        }
        mAxisList.append(rect);

        QCPItemStraightLine* line = new QCPItemStraightLine(mSignalPlot);
        line->setClipAxisRect(rect);
        line->setLayer("overlay");
        line->setPen(QPen(Qt::black, 1, Qt::SolidLine));//设置游标线的样式
        line->setClipToAxisRect(true);//自适应范围
        line->setVisible(true);
        QCPRange keyRange = rect->axis(QCPAxis::atBottom)->range();
        line->point1->setCoords(mFrameId, keyRange.upper);//起点坐标
        line->point2->setCoords(mFrameId, keyRange.lower);//终点坐标

        mCursorList.append(line);

    }
    connectAllxAsix(true);

}

void SignalView::initPlot()
{
    // 初始化信号曲线UI
    // 1 视图
    mSignalPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    mSignalPlot->setSelectionRectMode(QCP::SelectionRectMode::srmNone);//模式：框选放大
    mSignalPlot->legend->setVisible(false);
    //mSignalPlot->legend->setSelectableParts(QCPLegend::spItems);     //设置legend
    //mSignalPlot->legend->setFont(QFont("Helvetica", 9));
    //mSignalPlot->legend->setRowSpacing(-3);
    //mSignalPlot->xAxis->setVisible(true);
    //mSignalPlot->xAxis->grid()->setVisible(false);
    //mSignalPlot->yAxis->grid()->setVisible(false);
    //mSignalPlot->yAxis->setLabelColor(Qt::white);
    mSignalPlot->plotLayout()->clear();   // 首先清空默认的轴矩形，让我们从头开始


    // 3 曲线

}


void SignalView::initCursor()
{
    // 2 游标
#if 0
    m_lineCursor = new QCPItemStraightLine(mSignalPlot);
    m_lineCursor->setLayer("overlay");
    m_lineCursor->setPen(QPen(Qt::black, 1, Qt::SolidLine));//设置游标线的样式
    m_lineCursor->setClipToAxisRect(true);//自适应范围
    m_lineCursor->setVisible(false);
#endif
}


QString colorToString(const QColor& color)
{
    // 拆解r, g, b
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    
    // 转hex string
    QString hexRed = QString::number(red, 16);
    QString hexGreen = QString::number(green, 16);
    QString hexBlue = QString::number(blue, 16);
    
    // 拼接
    QString colorStr = "#" + hexRed + hexGreen + hexBlue;
    return colorStr;
}


void SignalView::showTable()
{
    // 添加数据
    for (int i = 0; i < mTotalSignal; i++)
    {
        // 信号
        QStandardItem* itemSig = new QStandardItem();
        itemSig->setCheckable(true);
        itemSig->setCheckState(Qt::Checked);
        itemSig->setEditable(false);
        itemSig->setText(mNameVec->at(i));
        mTableModel->setItem(i, 0, itemSig);
        
        // 颜色
        QStandardItem* itemColor = new QStandardItem();
        itemColor->setEditable(false);
        //itemColor->setBackground(QBrush(m_colorVec->at(i)));
        itemColor->setData(mColorVec->at(i), Qt::DecorationRole);
        mTableModel->setItem(i, 1, itemColor);

        // 值
        QStandardItem* itemValue = new QStandardItem();
        itemValue->setEditable(false);
        auto valueList = mSignalVec->at(i);
        //itemValue->setText(QString::number(m_signalVec->at(i).at(m_frameId)));
        mTableModel->setItem(i, 2, itemValue);
    }
	mTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);  // 固定第一列
	mTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed); // 第二列可拉伸
	mTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed); // 第二列可拉伸
}


void plotSignal(QCPAxisRect* rect, const QString& sigName, QColor color, const QVector<double>& signal, bool visibleState)
{
    QVector<double> vecPointX;
    QVector<double> vecPointY;

    for (auto iFrame = 0; iFrame < signal.size(); ++iFrame)
    {
        vecPointX.append(iFrame);
        vecPointY.append(signal[iFrame]);
    }
    
    //QCPGraph* graph = new QCPGraph(plot->xAxis, plot->yAxis);
    QCPGraph* graph = new QCPGraph(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
    graph->setName(sigName);
    graph->setPen(QPen(color, 1));
    graph->setAntialiased(false);
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 2));
    graph->setAdaptiveSampling(true);
    graph->setData(vecPointX, vecPointY, true);
    graph->setVisible(visibleState);
    graph->rescaleAxes(true);

}


void SignalView::showPlot()
{
    // 绘图
    RemoveQCPAxisRectAll();
    if (mSelectSignal < MAX_SHOW_SIGNAL_NUM)
    {
        CreateQCPAxisRect(mSelectSignal);
        auto sigId = 0;
        for (int i = 0; i < mTableModel->rowCount(); i++)
        {
            if (mCheckVec->at(i))
            {
                plotSignal(mAxisList.at(sigId), mNameVec->at(i), mColorVec->at(i), mSignalVec->at(i), mCheckVec->at(i));
                sigId++;
            }

        }
    }
    mSignalPlot->replot();
}


void SignalView::showCursor()
{
    for (auto iCur = 0; iCur < mCursorList.count(); ++iCur)
    {
        QCPRange keyRange = mAxisList.at(iCur)->axis(QCPAxis::atBottom)->range();
        mCursorList.at(iCur)->point1->setCoords(mFrameId, keyRange.upper);//起点坐标
        mCursorList.at(iCur)->point2->setCoords(mFrameId, keyRange.lower);//终点坐标
        mCursorList.at(iCur)->setVisible(true);
    }

}


void SignalView::updateTable(size_t frame)
{
#if 0
    for (int iSig = 0; iSig < m_totalSignal; iSig++)
    {
        // 值
        mTableModel->setItem(iSig, 2, new QStandardItem(QString::number(m_signalVec->at(iSig).at(frame))));
    }
#endif
}



void SignalView::updatePlot(size_t frame)
{

}


void initTracer(QCPItemTracer* tracer)
{
    tracer->setObjectName("Tracer");
    tracer->setStyle(QCPItemTracer::tsCircle);        // 标记点的类型设置为圆形
    tracer->setPen(QPen(Qt::red, 3, Qt::SolidLine));  // 标记点颜色、粗细、线型
    tracer->setBrush(Qt::SolidPattern);               // 画刷

    tracer->position->setType(QCPItemPosition::ptPlotCoords);// 在曲线上显示
    tracer->setSize(3);
}


void initText(QCPItemText* labelText)
{
    // 置跟随锚点的位置
    labelText->setFont(QFont(qApp->font().family(), 8));      // 设置字体大小
    labelText->setColor(Qt::black);                            // 设置字体颜色
    labelText->setBrush(Qt::green);
    //labelText->setPadding(QMargins(4, 4, 4, 4));                        // 文字距离边框几个像素

    // 设置标签对齐方式
    labelText->setPositionAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}


void initLine(QCPItemLine* arrowLine)
{
    arrowLine->setObjectName("Tracer");
    arrowLine->setPen(QPen(Qt::green, 1));
    arrowLine->setHead(QCPLineEnding::esSpikeArrow);//设置箭头类型（三角形、菱形、方形等）
    arrowLine->setVisible(true);
}


void SignalView::updateCursor(size_t frame)
{
    for (auto iCur = 0; iCur < mCursorList.count(); ++iCur)
    {
        QCPRange keyRange = mAxisList.at(iCur)->axis(QCPAxis::atBottom)->range();
        mCursorList.at(iCur)->point1->setCoords(frame, keyRange.upper);//起点坐标
        mCursorList.at(iCur)->point2->setCoords(frame, keyRange.lower);//终点坐标
    }

    mSignalPlot->replot();

#if 0
    // 清空标记点和标签
    for (auto i = mSignalPlot->itemCount() - 1; i > -1; --i)
    {
        if (mSignalPlot->item(i)->objectName().contains("Tracer"))
        {
            mSignalPlot->removeItem(i);
        }
    }
    // 标记点和标签
    for (auto i = 0; i < mSignalPlot->graphCount(); ++i)
    {
        if (mSignalPlot->graph(i)->visible())
        {
            double y_value = mSignalPlot->graph(i)->data()->at(frame)->value;                     //获取曲线在X轴位置的Y值
            QCPItemTracer* tracer = new QCPItemTracer(mSignalPlot);        //设置部件的父类
            initTracer(tracer);
            tracer->position->setCoords(frame, y_value);             //设置标记点在位置

            QCPItemText* labelText = new QCPItemText(mSignalPlot);//文本框父类设置
            initText(labelText);
            labelText->position->setParentAnchor(tracer->position);
            QString text = mSignalPlot->graph(i)->name()
                + " x:" + QString::number(frame)
                + " y:" + QString::number(y_value);
            labelText->setText(text);
            labelText->position->setCoords(30, -30);

            QCPItemLine* arrowLine = new QCPItemLine(mSignalPlot);
            initLine(arrowLine);
            arrowLine->start->setParentAnchor(labelText->bottom);  //设置该直线的起点为文字框的下锚点
            arrowLine->end->setCoords(frame, y_value); //设置直线终点为坐标系中的点
        }

    }
#endif 
}


void SignalView::onTableSelected(const QModelIndex& index)
{
    // 获取选中行状态
    int row = index.row();
    bool flag = false;

    // 获取多行选中列表
    QItemSelectionModel* modelSelection = mTableView->selectionModel();
    QModelIndexList indexList = modelSelection->selectedIndexes();

    for (auto iChk = 0; iChk < mCheckVec->size(); ++iChk)
    {
        (*mCheckVec)[iChk] = false;
    }
    // 获取选中信号名列表
    mSelectSignal = 0;
    for (auto iRow = 0; iRow < indexList.size() / mTableModel->columnCount(); ++iRow)
    {
        QModelIndex index = indexList.at(iRow * mTableModel->columnCount());
        if (mTableModel->item(index.row(), 0)->checkState())
        {
            (*mCheckVec)[index.row()] = true;
            mSelectSignal++;
        }
    }
    showPlot();
    mSignalPlot->replot();

}


void SignalView::onMousePress(QMouseEvent* event)
{
    auto rectId = 0;
    for (auto iRect = 0; iRect < mAxisList.count(); ++iRect)
    {
        if (mAxisList.at(iRect)->rect().contains(event->pos()))
        {
            rectId = iRect;
        }
    }

    if (!mCursorList.isEmpty())
    {
        double distanceLV = mCursorList.at(rectId)->selectTest(event->pos(), false);

        //定义游标标识，由上面的距离来决定移动那根游标
        if (event->button() == Qt::RightButton && distanceLV <= Globals::ChangeCursorStyleDistance)
        {
            mCursorSelectFlag = true;
        }
        else
        {
            mCursorSelectFlag = false;
        }

        //当前鼠标位置（像素坐标）
        if (event->button() == Qt::RightButton)
        {
            size_t xVal = mAxisList.at(rectId)->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x());
            if (xVal < 0)
            {
                xVal = 0;
            }
            else if (xVal > mTotalFrame)
            {
                xVal = mTotalFrame - 1;
            }
            updateCursor(xVal);
            updateTable(xVal);
            emit frameChanged(xVal);
        }
    }
    
}


void SignalView::onMouseMove(QMouseEvent* event)
{
    // 当前鼠标位置（像素坐标）
    auto rectId = 0;
    for (auto iRect = 0; iRect < mAxisList.count(); ++iRect)
    {
        if (mAxisList.at(iRect)->rect().contains(event->pos()))
        {
            rectId = iRect;
            // 像素坐标转成实际的x,y轴的坐标
            auto xVal = mAxisList.at(rectId)->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x());

            //获取距离
            auto distance = mCursorList.at(rectId)->selectTest(event->pos(), false);

            //当鼠标在游标上时改变鼠标形状
            if (distance <= Globals::ChangeCursorStyleDistance)
            {
                mSignalPlot->setCursor(Qt::ClosedHandCursor);
            }
            else
            {
                mSignalPlot->setCursor(Qt::ArrowCursor);
            }

            // 游标移动判断
            if (mCursorSelectFlag)
            {
                for (auto cursor : mCursorList)
                {
                    cursor->setPen(QPen(Qt::blue, 2, Qt::SolidLine));
                }
                if (xVal < 0)
                {
                    xVal = 0;
                }
                else if (xVal > mTotalFrame)
                {
                    xVal = mTotalFrame - 1;
                }

                updateCursor(xVal);
                updateTable(xVal);
                emit frameChanged(xVal);
            }
        }
    }
    
}


void SignalView::onMouseRelease(QMouseEvent* event)
{
    mCursorSelectFlag = false;
    for (auto cursor : mCursorList)
    {
        cursor->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    }
    mSignalPlot->replot();
}

void SignalView::onSelectionChanged()
{
#if 0
    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (mSignalPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || mSignalPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        mSignalPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || mSignalPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        mSignalPlot->xAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
        mSignalPlot->xAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (mSignalPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || mSignalPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        mSignalPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || mSignalPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        mSignalPlot->yAxis2->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
        mSignalPlot->yAxis->setSelectedParts(QCPAxis::spAxis | QCPAxis::spTickLabels);
    }

    // 将图形的选择与相应图例项的选择同步
    for (int i = 0; i < mSignalPlot->graphCount(); ++i)
    {
        QCPGraph* graph = mSignalPlot->graph(i);
        QCPPlottableLegendItem* item = mSignalPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }
#endif
}



#endif