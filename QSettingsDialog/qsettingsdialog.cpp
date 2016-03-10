#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include <QListWidgetItem>
#include <dialogmaster.h>
#include "qsettingssection.h"

#define TEST_DEFAULT(index) (d->defaultCategory ? (index + 1) : (index))

QSettingsDialog::QSettingsDialog(QObject *parent) :
	QObject(parent),
	d_ptr(new QSettingsDialogPrivate(this))
{
	this->resetCategoryIconSize();
}

QSettingsDialog::~QSettingsDialog() {}

QList<QSettingsCategory *> QSettingsDialog::categories(bool includeDefault) const
{
	const Q_D(QSettingsDialog);
	QList<QSettingsCategory *> cats = d->categories;
	if(includeDefault && d->defaultCategory)
		cats.prepend(d->defaultCategory);
	return cats;
}

int QSettingsDialog::categoryCount() const
{
	const Q_D(QSettingsDialog);
	return d->categories.size();
}

QSettingsCategory *QSettingsDialog::categoryAt(int index) const
{
	const Q_D(QSettingsDialog);
	Q_ASSERT_X2(index >= 0 && index < d->categories.size(), "index out of range");
	return d->categories.at(index);
}

int QSettingsDialog::categoryIndex(QSettingsCategory *category) const
{
	const Q_D(QSettingsDialog);
	return d->categories.indexOf(category);
}

QSettingsCategory *QSettingsDialog::insertCategory(int index, const QString &name, const QIcon &icon, const QString &toolTip)
{
	Q_D(QSettingsDialog);
	Q_ASSERT_X2(index >= 0 && index <= d->categories.size(), "index out of range");
	QSettingsCategory *cat = d->createCategory(TEST_DEFAULT(index), name, icon, toolTip);
	d->categories.insert(index, cat);

	return cat;
}

QSettingsCategory *QSettingsDialog::addCategory(const QString &name, const QIcon &icon, const QString &toolTip)
{
	const Q_D(QSettingsDialog);
	return this->insertCategory(d->categories.size(), name, icon, toolTip);
}

void QSettingsDialog::deleteCategory(int index)
{
	Q_D(QSettingsDialog);
	Q_ASSERT_X2(index >= 0 && index < d->categories.size(), "index out of range");
	d->mainDialog->deleteItem(TEST_DEFAULT(index));
	delete d->categories.takeAt(index);
}

bool QSettingsDialog::deleteCategory(QSettingsCategory *category)
{
	Q_D(QSettingsDialog);
	int index = d->categories.indexOf(category);
	if(index >= 0) {
		this->deleteCategory(index);
		return true;
	} else
		return false;
}

void QSettingsDialog::moveCategory(int from, int to)
{
	Q_D(QSettingsDialog);
	Q_ASSERT_X2(from >= 0 && from < d->categories.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to < d->categories.size(), "index out of range");
	d->categories.move(from, to);
	d->mainDialog->moveItem(TEST_DEFAULT(from), TEST_DEFAULT(to));
}

QSettingsCategory *QSettingsDialog::defaultCategory()
{
	Q_D(QSettingsDialog);
	if(!d->defaultCategory) {
		d->defaultCategory = d->createCategory(0,
											   tr("General"),
											   QIcon(QStringLiteral(":/QSettingsDialog/icons/general.ico")));
	}
	return d->defaultCategory;
}

QSettingsSection *QSettingsDialog::defaultSection()
{
	return this->defaultCategory()->defaultSection();
}

QSettingsGroup *QSettingsDialog::defaultGroup()
{
	return this->defaultCategory()->defaultSection()->defaultGroup();
}

bool QSettingsDialog::hasDefaultCategory() const
{
	const Q_D(QSettingsDialog);
	return d->defaultCategory;
}

QSize QSettingsDialog::categoryIconSize() const
{
	const Q_D(QSettingsDialog);
	return d->mainDialog->iconSize();
}

void QSettingsDialog::showDialog()
{
	Q_D(QSettingsDialog);
	d->startLoading();
	d->mainDialog->open();
}

void QSettingsDialog::setCategoryIconSize(QSize categoryIconSize)
{
	Q_D(QSettingsDialog);
	d->mainDialog->updateIconSize(categoryIconSize);
}

void QSettingsDialog::resetCategoryIconSize()
{
	Q_D(QSettingsDialog);
	int size = d->mainDialog->style()->pixelMetric(QStyle::PM_LargeIconSize);
	d->mainDialog->updateIconSize({size, size});
}

void QSettingsDialog::loadDone(const QVariant &data, bool isUser)
{
	Q_D(QSettingsDialog);
	if(d->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "loadDone signal from wrong sender received");
		d->progressDialog->setValue(++d->currentMax);
		QSettingsWidgetBase *widget = d->entryMap.value(loader);
		if(widget->optBox)
			widget->optBox->setChecked(isUser);
		if(isUser)
			widget->group->setActive(true);
		if(!data.isNull())
			widget->setValue(data);
		else
			widget->resetValue();
		if(d->currentMax == d->progressDialog->maximum()) {
			d->progressDialog->deleteLater();
			d->progressDialog = Q_NULLPTR;
			d->mainDialog->setEnabled(true);
		}
	}
}

void QSettingsDialog::saveDone(bool successfull)
{
	Q_D(QSettingsDialog);
	if(d->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "saveDone signal from wrong sender received");
		d->progressDialog->setValue(++d->currentMax);
		if(!successfull) {
			d->progressDialog->cancel();
			d->progressDialog->deleteLater();
			d->progressDialog = Q_NULLPTR;
			d->mainDialog->setEnabled(true);
			DialogMaster::critical(d->mainDialog,
								   tr("Failed to save settings!"));
		} else if(d->currentMax == d->progressDialog->maximum()) {
			d->progressDialog->deleteLater();
			d->progressDialog = Q_NULLPTR;
			d->mainDialog->setEnabled(true);
			if(d->closeDown)
				d->mainDialog->accept();
		}
	}
}

void QSettingsDialog::resetDone(bool successfull)
{
	Q_D(QSettingsDialog);
	if(d->progressDialog) {
		QSettingsLoader *loader = qobject_cast<QSettingsLoader*>(QObject::sender());
		Q_ASSERT_X2(loader, "resetDone signal from wrong sender received");
		d->progressDialog->setValue(++d->currentMax);
		if(!successfull) {
			d->progressDialog->cancel();
			d->progressDialog->deleteLater();
			d->progressDialog = Q_NULLPTR;
			d->mainDialog->setEnabled(true);
			DialogMaster::critical(d->mainDialog,
								   tr("Failed to restore default settings!"));
		} else if(d->currentMax == d->progressDialog->maximum()) {
			d->progressDialog->deleteLater();
			d->progressDialog = Q_NULLPTR;
			d->mainDialog->setEnabled(true);
			d->mainDialog->accept();
		}
	}
}

// ------------------------- PRIVATE IMPLEMENTATION -------------------------

QSettingsDialogPrivate::QSettingsDialogPrivate(QSettingsDialog *q_ptr) :
	q_ptr(q_ptr),
	mainDialog(new DisplayDialog(this, Q_NULLPTR)),
	defaultCategory(Q_NULLPTR),
	categories(),
	progressDialog(Q_NULLPTR),
	currentMax(0),
	closeDown(false),
	entryMap()
{}

QSettingsDialogPrivate::~QSettingsDialogPrivate()
{
	delete this->defaultCategory;
	foreach (QSettingsCategory *cat, this->categories)
		delete cat;
	Q_ASSERT_X2(this->entryMap.isEmpty(), "Some entries have not been unloaded properly");
}

void QSettingsDialogPrivate::addSettingsEntry(QSettingsEntry *entry, QSettingsWidgetBase *widget)
{
	Q_Q(QSettingsDialog);
	QSettingsLoader *loader = entry->getLoader();
	Q_ASSERT_X2(loader, "loader with NULL-value passed");
	QObject::connect(loader, &QSettingsLoader::loadDone,
					 q, &QSettingsDialog::loadDone,
					 Qt::QueuedConnection);
	QObject::connect(loader, &QSettingsLoader::saveDone,
					 q, &QSettingsDialog::saveDone,
					 Qt::QueuedConnection);
	QObject::connect(loader, &QSettingsLoader::resetDone,
					 q, &QSettingsDialog::resetDone,
					 Qt::QueuedConnection);
	this->entryMap.insert(loader, widget);
}

void QSettingsDialogPrivate::removeSettingsEntry(QSettingsEntry *entry)
{
	Q_Q(QSettingsDialog);
	QSettingsLoader *loader = entry->getLoader();
	Q_ASSERT_X2(loader, "loader with NULL-value passed");
	QObject::disconnect(loader, &QSettingsLoader::loadDone,
						q, &QSettingsDialog::loadDone);
	QObject::disconnect(loader, &QSettingsLoader::saveDone,
						q, &QSettingsDialog::saveDone);
	QObject::disconnect(loader, &QSettingsLoader::resetDone,
						q, &QSettingsDialog::resetDone);
	this->entryMap.remove(loader);
}

void QSettingsDialogPrivate::startSaving(bool closeDown)
{
	this->closeDown = closeDown;
	this->currentMax = 0;
	this->mainDialog->setEnabled(false);
	this->progressDialog = DialogMaster::createProgress(this->mainDialog,
														QSettingsDialog::tr("Saving settings…"),
														this->entryMap.size(),
														0,
														false,
														QString(),
														1000);
	for(const_iter it = this->entryMap.constBegin(), end = this->entryMap.constEnd(); it != end; ++it) {
		if(!it.value()->group->isActivated() ||
		   it.value()->optBox && !it.value()->optBox->isChecked()) {
			QMetaObject::invokeMethod(it.key(), "resetData", Qt::QueuedConnection);
		} else {
			QVariant value = it.value()->getValue();
			QMetaObject::invokeMethod(it.key(), "saveData", Qt::QueuedConnection,
									  Q_ARG(QVariant, value));
		}
	}
}

void QSettingsDialogPrivate::discard()
{
	foreach(QSettingsWidgetBase *widget, this->entryMap)
		widget->resetValue();
}

void QSettingsDialogPrivate::reset()
{
	this->currentMax = 0;
	this->mainDialog->setEnabled(false);
	this->progressDialog = DialogMaster::createProgress(this->mainDialog,
														QSettingsDialog::tr("Restoring defaults…"),
														this->entryMap.size(),
														0,
														false,
														QString(),
														1000);
	foreach(QSettingsLoader *loader, this->entryMap.keys())
		QMetaObject::invokeMethod(loader, "resetData", Qt::QueuedConnection);
}

QSettingsCategory *QSettingsDialogPrivate::createCategory(int index, const QString &name, const QIcon &icon, const QString &toolTip)
{
	QListWidgetItem *item = new QListWidgetItem();
	item->setText(name);
	item->setIcon(icon);
	item->setToolTip(toolTip.isNull() ? name : toolTip);
	QTabWidget *tab = new QTabWidget();
	tab->setTabBarAutoHide(true);

	this->mainDialog->insertItem(index, item, tab);
	return new QSettingsCategory(item, !toolTip.isNull(), tab, this);
}

void QSettingsDialogPrivate::startLoading()
{
	this->currentMax = 0;
	QMetaObject::invokeMethod(this->mainDialog, "setEnabled", Qt::QueuedConnection,
							  Q_ARG(bool, false));//TODO fails for whatever reason...
	this->progressDialog = DialogMaster::createProgress(this->mainDialog,
														QSettingsDialog::tr("Loading settings…"),
														this->entryMap.size(),
														0,
														false,
														QString(),
														1000);
	for(const_iter it = this->entryMap.constBegin(), end = this->entryMap.constEnd(); it != end; ++it) {
		it.value()->group->setActive(false);//TODO
		QMetaObject::invokeMethod(it.key(), "loadData", Qt::QueuedConnection);
	}
}
