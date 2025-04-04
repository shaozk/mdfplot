#include "SignalExplorer.h"
#include "SignalListModel.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QTreeView>
#include <QFrame>
#include <QLineEdit>

#include "Signals.h"

SignalExplorer::SignalExplorer(QWidget* parent)
    : mSignalView(new QTreeView(parent))
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
	mSearchEdit->setPlaceholderText("Search");
	layoutFilter->addWidget(mSearchEdit);

	mSearchBtn = new QPushButton(mSearchFrame);
	mSearchBtn->setIcon(QIcon::fromTheme(QStringLiteral("configure")));
	mSearchBtn->setText("Search");
	layoutFilter->addWidget(mSearchBtn);

	mCancelBtn = new QPushButton(mSearchFrame);
	mCancelBtn->setIcon(QIcon::fromTheme(QStringLiteral("configure")));
	mCancelBtn->setText("Cancel");
	connect(mCancelBtn, &QPushButton::clicked, this, [this]() {
		mSearchEdit->clear();
		mSignalView->clearSelection();
		emit signalCanceled();
	});
	layoutFilter->addWidget(mCancelBtn);

	layout->addWidget(mSearchFrame);

	mSignalView->setAlternatingRowColors(true);
	mSignalView->setSelectionBehavior(QAbstractItemView::SelectRows);
	mSignalView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	mSignalView->viewport()->installEventFilter(this);
	mSignalView->setDragEnabled(true);
	mSignalView->setAcceptDrops(true);
	mSignalView->setDropIndicatorShown(true);
	mSignalView->setDragDropMode(QAbstractItemView::InternalMove);
	mSignalView->header()->sectionResizeMode(QHeaderView::Stretch);
	layout->addWidget(mSignalView);

	connect(mSignalView, &QTreeView::clicked, this, &SignalExplorer::signalClicked);

}

SignalExplorer::~SignalExplorer()
{

}

void SignalExplorer::setModel(SignalListModel* model)
{
	mSignalView->setModel(std::move(model));
	/// connect(model, &SignalListModel::signalSelected, this, &SignalExplorer::signalSelected)
	

}

void SignalExplorer::signalClicked(const QModelIndex& index)
{
	auto* model = qobject_cast<SignalListModel*>(mSignalView->model());
	if (model)
	{
		const auto* signal = model->getSignal(index);
		emit signalSelected(signal);
	}
}
