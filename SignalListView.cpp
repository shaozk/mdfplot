#include "SignalListView.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>

SignalListView::SignalListView(QWidget* parent)
    : QWidget(parent)
    , mView(new QTableView(this))
{
    setLayout(new QVBoxLayout(this));
    layout()->addWidget(mView);
    mView->setAutoFillBackground(true);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

SignalListView::~SignalListView()
{

}

void SignalListView::on_listWidget_itemClicked(QListWidgetItem *item)
{
    // 获取选中行状态
    auto signalName = item->text();
    qDebug() << signalName;


}

