#include "SignalListView.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>

SignalListView::SignalListView(QWidget* parent)
    : QTableView(parent)
{
    setAutoFillBackground(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

SignalListView::~SignalListView()
{

}


void SignalListView::mousePressEvent(QMouseEvent* event)
{
    
    // 调用基类的实现以确保默认行为
    QTableView::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid())
        {
            emit signalSelected(QString::number(index.row()));
        }
    }
    
}

