#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include "ui_qsettingsdialog.h"
#include "qsettingssection.h"

#define TEST_DEFAULT(index) (d->defaultCategory ? (index + 1) : (index))

QSettingsDialog::QSettingsDialog(QWidget *parent) :
	QDialog(parent),
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

	QWidget *w = d->ui->contentStackWidget->widget(TEST_DEFAULT(index));
	d->ui->contentStackWidget->removeWidget(w);
	w->deleteLater();
	delete d->ui->categoryListWidget->item(TEST_DEFAULT(index));
	d->resetListSize();

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

	QWidget *w = d->ui->contentStackWidget->widget(TEST_DEFAULT(from));
	d->ui->contentStackWidget->removeWidget(w);
	d->ui->contentStackWidget->insertWidget(TEST_DEFAULT(to), w);
	QListWidgetItem *item = d->ui->categoryListWidget->takeItem(TEST_DEFAULT(from));
	d->ui->categoryListWidget->insertItem(TEST_DEFAULT(to), item);
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
	return d->ui->categoryListWidget->iconSize();
}

void QSettingsDialog::setCategoryIconSize(QSize categoryIconSize)
{
	Q_D(QSettingsDialog);
	d->ui->categoryListWidget->setIconSize(categoryIconSize);
}

void QSettingsDialog::resetCategoryIconSize()
{
	Q_D(QSettingsDialog);
	int size = this->style()->pixelMetric(QStyle::PM_LargeIconSize);
	d->ui->categoryListWidget->setIconSize({size, size});
}

void QSettingsDialog::showEvent(QShowEvent *event)
{
	Q_D(QSettingsDialog);
	d->startLoading();

	d->ui->categoryListWidget->setCurrentItem(d->ui->categoryListWidget->item(0));
	for(int i = 0, max = d->ui->contentStackWidget->count(); i < max; ++i) {
		QTabWidget *tab = qobject_cast<QTabWidget*>(d->ui->contentStackWidget->widget(i));
		if(tab)
			tab->setCurrentIndex(0);
	}
	this->QDialog::showEvent(event);
}
