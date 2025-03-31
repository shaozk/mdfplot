#include "SignalExplorer.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QFrame>
#include <QLineEdit>

SignalExplorer::SignalExplorer(QWidget* parent)
    : mSignalView(new QListView(parent))
    , mSearchFrame(new QFrame(this))
{
    auto* layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	auto* layoutFilter = new QHBoxLayout(mSearchFrame);
	layoutFilter->setSpacing(0);
	layoutFilter->setContentsMargins(0, 0, 0, 0);

	mSearchEdit = new QLineEdit(mSearchFrame);
	mSearchEdit->setClearButtonEnabled(true);
	mSearchEdit->setPlaceholderText("Search/Filter");
	layoutFilter->addWidget(mSearchEdit);

	mSearchBtn = new QPushButton(mSearchFrame);
	mSearchBtn->setIcon(QIcon::fromTheme(QStringLiteral("configure")));
	// mSearchBtn->setCheckable(true);
	// mSearchBtn->setFlat(true);
	mSearchBtn->setText("Search");
	layoutFilter->addWidget(mSearchBtn);

	layout->addWidget(mSearchFrame);

	mSignalView->setAlternatingRowColors(true);
	mSignalView->setSelectionBehavior(QAbstractItemView::SelectRows);
	mSignalView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	mSignalView->viewport()->installEventFilter(this);
	mSignalView->setDragEnabled(true);
	mSignalView->setAcceptDrops(true);
	mSignalView->setDropIndicatorShown(true);
	mSignalView->setDragDropMode(QAbstractItemView::InternalMove);

	layout->addWidget(mSignalView);

}

SignalExplorer::~SignalExplorer()
{

}

void SignalExplorer::setModel(SignalListModel* model)
{
	//mSignalView->setModel(model);
}