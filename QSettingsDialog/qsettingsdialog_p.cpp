#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include "ui_qsettingsdialog.h"
#include <QListWidgetItem>
#include <QtMath>
#include <dialogmaster.h>

QSettingsDialogPrivate::QSettingsDialogPrivate(QSettingsDialog *q_ptr) :
	QObject(q_ptr),
	q_ptr(q_ptr),
	defaultCategory(Q_NULLPTR),
	categories(),
	ui(new Ui::QSettingsDialog),
	delegate(Q_NULLPTR),
	maxWidthBase(0),
	progressDialog(Q_NULLPTR),
	currentValue(0),
	closeDown(false),
	entryMap()
{
	this->ui->setupUi(this->q_ptr);
	DialogMaster::masterDialog(this->q_ptr);
	connect(this->ui->buttonBox, &QDialogButtonBox::clicked,
			this, &QSettingsDialogPrivate::buttonBoxClicked);

	int listSpacing = this->q_ptr->style()->pixelMetric(QStyle::PM_LayoutVerticalSpacing);
	this->delegate = new CategoryItemDelegate(std::bind(&QSettingsDialogPrivate::updateWidth, this, std::placeholders::_1),
											  qMax(qRound(listSpacing * (2./3.)), 1),
											  this);
	this->delegate->setIconSize(this->ui->categoryListWidget->iconSize());
	this->ui->categoryListWidget->setItemDelegate(this->delegate);
	this->ui->categoryListWidget->setSpacing(qMax(qRound(listSpacing / 3.), 1) - 1);

	int spacing = this->q_ptr->style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing);
	this->ui->contentLayout->setSpacing(spacing);
	this->ui->categoryLineSpacer->changeSize(spacing,
											 0,
											 QSizePolicy::Fixed,
											 QSizePolicy::Fixed);

	connect(this->ui->categoryListWidget, &QListWidget::iconSizeChanged,
			this->delegate, &CategoryItemDelegate::setIconSize);

	this->resetListSize();
}

QSettingsDialogPrivate::~QSettingsDialogPrivate()
{
	delete this->defaultCategory;
	foreach (QSettingsCategory *cat, this->categories)
		delete cat;
	Q_ASSERT_X2(this->entryMap.isEmpty(), "Some entries have not been unloaded properly");
	delete this->ui;
}

void QSettingsDialogPrivate::addSettingsEntry(QSettingsEntry *entry, QSettingsWidgetBase *widget)
{
	QSettingsLoader *loader = entry->getLoader();
	Q_ASSERT_X2(loader, "loader with NULL-value passed");
	QObject::connect(loader, &QSettingsLoader::loadDone,
					 this, &QSettingsDialogPrivate::loadDone,
					 Qt::QueuedConnection);
	QObject::connect(loader, &QSettingsLoader::saveDone,
					 this, &QSettingsDialogPrivate::saveDone,
					 Qt::QueuedConnection);
	QObject::connect(loader, &QSettingsLoader::resetDone,
					 this, &QSettingsDialogPrivate::resetDone,
					 Qt::QueuedConnection);
	this->entryMap.insert(loader, widget);
}

void QSettingsDialogPrivate::removeSettingsEntry(QSettingsEntry *entry)
{
	QSettingsLoader *loader = entry->getLoader();
	Q_ASSERT_X2(loader, "loader with NULL-value passed");
	QObject::disconnect(loader, &QSettingsLoader::loadDone,
						this, &QSettingsDialogPrivate::loadDone);
	QObject::disconnect(loader, &QSettingsLoader::saveDone,
						this, &QSettingsDialogPrivate::saveDone);
	QObject::disconnect(loader, &QSettingsLoader::resetDone,
						this, &QSettingsDialogPrivate::resetDone);
	this->entryMap.remove(loader);
}

void QSettingsDialogPrivate::startSaving(bool closeDown)
{
	Q_Q(QSettingsDialog);
	this->closeDown = closeDown;
	this->currentValue = 0;
	this->setEditable(false);

	int max = 0;
	for(const_iter it = this->entryMap.constBegin(), end = this->entryMap.constEnd(); it != end; ++it) {
		if(it.value()->hasChanges()) {
			if(it.value()->isActive()) {
				max++;
				QVariant value = it.value()->getValue();
				QMetaObject::invokeMethod(it.key(), "saveData", Qt::QueuedConnection,
										  Q_ARG(QVariant, value));
			} else {
				max++;
				QMetaObject::invokeMethod(it.key(), "resetData", Qt::QueuedConnection);
			}
		}
	}

	if(max == 0) {
		this->setEditable(true);
		if(this->closeDown)
			q->accept();
	} else {
		this->progressDialog = DialogMaster::createProgress(q,
															QSettingsDialog::tr("Saving settings…"),
															max);
		QObject::connect(this->progressDialog, &QProgressDialog::canceled,
						 this, &QSettingsDialogPrivate::progressCanceled,
						 Qt::QueuedConnection);
	}
}

void QSettingsDialogPrivate::discard()
{
	foreach(QSettingsWidgetBase *widget, this->entryMap)
		widget->resetValue();
}

void QSettingsDialogPrivate::reset()
{
	Q_Q(QSettingsDialog);
	this->closeDown = true;
	this->currentValue = 0;
	this->setEditable(false);
	this->progressDialog = DialogMaster::createProgress(q,
														QSettingsDialog::tr("Restoring defaults…"),
														this->entryMap.size());
	QObject::connect(this->progressDialog, &QProgressDialog::canceled,
					 this, &QSettingsDialogPrivate::progressCanceled,
					 Qt::QueuedConnection);
	foreach(QSettingsLoader *loader, this->entryMap.keys())
		QMetaObject::invokeMethod(loader, "resetData", Qt::QueuedConnection);
}

void QSettingsDialogPrivate::loadDone(const QVariant &data, bool isUserEdited)
{
	if(this->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "loadDone signal from wrong sender received");
		this->progressDialog->setValue(++this->currentValue);

		QSettingsWidgetBase *widget = this->entryMap.value(loader);
		if(widget) {
			if(!data.isNull())
				widget->setValue(data);
			else
				widget->resetValue();
			widget->setLoadState(isUserEdited);
		}

		if(this->currentValue == this->progressDialog->maximum()) {
			foreach(QSettingsWidgetBase *widget, this->entryMap)
				widget->resetChanged();

			this->progressDialog->deleteLater();
			this->progressDialog = Q_NULLPTR;
			this->setEditable(true);
		}
	}
}

void QSettingsDialogPrivate::saveDone(bool successfull)
{
	Q_Q(QSettingsDialog);
	if(this->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "saveDone signal from wrong sender received");
		this->progressDialog->setValue(++this->currentValue);

		if(!successfull) {
			this->progressDialog->cancel();
			this->progressDialog->deleteLater();
			this->progressDialog = Q_NULLPTR;
			this->setEditable(true);
			DialogMaster::critical(q,
								   tr("Failed to save settings!"));
			return;
		}

		QSettingsWidgetBase *widget = this->entryMap.value(loader);
		if(widget)
			widget->resetChanged();

		if(this->currentValue == this->progressDialog->maximum()) {
			this->progressDialog->deleteLater();
			this->progressDialog = Q_NULLPTR;
			this->setEditable(true);
			if(this->closeDown)
				q->accept();
		}
	}
}

void QSettingsDialogPrivate::resetDone(bool successfull)
{
	Q_Q(QSettingsDialog);
	if(this->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "resetDone signal from wrong sender received");
		this->progressDialog->setValue(++this->currentValue);

		if(!successfull) {
			this->progressDialog->cancel();
			this->progressDialog->deleteLater();
			this->progressDialog = Q_NULLPTR;
			this->setEditable(true);
			DialogMaster::critical(q,
								   tr("Failed to restore default settings!"));
			return;
		}

		QSettingsWidgetBase *widget = this->entryMap.value(loader);
		if(widget)
			widget->resetChanged();

		if(this->currentValue == this->progressDialog->maximum()) {
			this->progressDialog->deleteLater();
			this->progressDialog = Q_NULLPTR;
			this->setEditable(true);
			if(this->closeDown)
				q->accept();
		}
	}
}

void QSettingsDialogPrivate::progressCanceled()
{
	Q_Q(QSettingsDialog);
	if(this->progressDialog) {//TODO proper canceling...
		this->progressDialog->deleteLater();
		this->progressDialog = Q_NULLPTR;
		this->discard();
		q->reject();
	}
}

void QSettingsDialogPrivate::resetListSize()
{
	int max = this->ui->categoryListWidget->count();
	if(max == 0)
		this->ui->categoryContentWidget->hide();
	else {
		this->maxWidthBase = 0;
		this->updateWidth(this->ui->categoryListWidget->sizeHint().width() * 0.8);
		this->ui->categoryContentWidget->show();
	}
}

void QSettingsDialogPrivate::updateWidth(int width)
{
	if(width > this->maxWidthBase) {
		this->maxWidthBase = width;
		QStyle *style = this->ui->categoryListWidget->style();
		width += style->pixelMetric(QStyle::PM_ScrollBarExtent);
		width += style->pixelMetric(QStyle::PM_LayoutHorizontalSpacing);
		this->ui->categoryListWidget->setFixedWidth(width);
	}
}

void QSettingsDialogPrivate::buttonBoxClicked(QAbstractButton *button)
{
	Q_Q(QSettingsDialog);
	switch(this->ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::Ok:
		this->startSaving(true);
		break;
	case QDialogButtonBox::Cancel:
		this->discard();
		q->reject();
		break;
	case QDialogButtonBox::Apply:
		this->startSaving(false);
		break;
	case QDialogButtonBox::RestoreDefaults:
		if(DialogMaster::warning(q,
								 tr("All custom changes will be delete and the defaults restored. "
									"This cannot be undone."),
								 tr("%1?").arg(button->text()),
								 QString(),
								 QMessageBox::Yes,
								 QMessageBox::No)
		   == QMessageBox::Yes) {
			this->reset();
		}
		break;
	default:
		Q_UNREACHABLE();
	}
}

QSettingsCategory *QSettingsDialogPrivate::createCategory(int index, const QString &name, const QIcon &icon, const QString &toolTip)
{
	QListWidgetItem *item = new QListWidgetItem();
	item->setText(name);
	item->setIcon(icon);
	item->setToolTip(toolTip.isNull() ? name : toolTip);
	QTabWidget *tab = new QTabWidget();
	tab->setTabBarAutoHide(true);

	this->ui->contentStackWidget->insertWidget(index, tab);
	this->ui->categoryListWidget->insertItem(index, item);
	this->resetListSize();
	return new QSettingsCategory(item, !toolTip.isNull(), tab, this);
}

void QSettingsDialogPrivate::startLoading()
{
	Q_Q(QSettingsDialog);
	this->currentValue = 0;
	this->setEditable(false);
	this->progressDialog = DialogMaster::createProgress(q,
														QSettingsDialog::tr("Loading settings…"),
														this->entryMap.size());
	QObject::connect(this->progressDialog, &QProgressDialog::canceled,
					 this, &QSettingsDialogPrivate::progressCanceled,
					 Qt::QueuedConnection);
	for(const_iter it = this->entryMap.constBegin(), end = this->entryMap.constEnd(); it != end; ++it) {
		it.value()->group->setActive(false);
		QMetaObject::invokeMethod(it.key(), "loadData", Qt::QueuedConnection);
	}
}

void QSettingsDialogPrivate::setEditable(bool editable)
{
	this->ui->contentStackWidget->setEnabled(editable);
	this->ui->buttonBox->setEnabled(editable);
}



CategoryItemDelegate::CategoryItemDelegate(std::function<void (int)> updateFunc, int layoutSpacing, QObject *parent) :
	QStyledItemDelegate(parent),
	spacing(layoutSpacing),
	extendSize(),
	updateFunc(updateFunc)
{}

void CategoryItemDelegate::setIconSize(const QSize &size)
{
	this->extendSize = size + QSize(0, this->spacing);
}

QSize CategoryItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize size = this->QStyledItemDelegate::sizeHint(option, index);
	this->updateFunc(size.width());
	return size.expandedTo(this->extendSize);
}
