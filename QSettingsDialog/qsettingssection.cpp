#include "qsettingssection.h"
#include <QTabBar>
#include "qsettingsgroup.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include "qsettingsdialog_p.h"

#define TEST_DEFAULT(index) (this->defaultGrp ? (index + 1) : (index))

QSettingsSection::QSettingsSection(QTabBar *tabBar, int tabIndex, QWidget *contentWidget, QSettingsDialogPrivate *priv) :
	priv(priv),
	tabBar(tabBar),
	tabIndex(tabIndex),
	contentWidget(contentWidget),
	defaultGrp(Q_NULLPTR),
	grps()
{
	QVBoxLayout *layout = new QVBoxLayout(this->contentWidget);
	this->contentWidget->setLayout(layout);
	layout->addStretch();
}

QSettingsSection::~QSettingsSection()
{
	delete this->defaultGrp;
	foreach(QSettingsGroup *group, this->grps)
		delete group;
}

void QSettingsSection::updateIndex(int tabIndex)
{
	this->tabIndex = tabIndex;
}

QString QSettingsSection::name() const
{
	return this->tabBar->tabText(this->tabIndex);
}

QIcon QSettingsSection::icon() const
{
	return this->tabBar->tabIcon(this->tabIndex);
}

void QSettingsSection::setName(const QString &name)
{
	this->tabBar->setTabText(this->tabIndex, name);
}

void QSettingsSection::setIcon(const QIcon &icon)
{
	this->tabBar->setTabIcon(this->tabIndex, icon);
}

QList<QSettingsGroup *> QSettingsSection::groups(bool includeDefault) const
{
	QList<QSettingsGroup *> groups = this->grps;
	if(includeDefault && this->defaultGrp)
		groups.prepend(this->defaultGrp);
	return groups;
}

int QSettingsSection::groupCount() const
{
	return this->grps.size();
}

QSettingsGroup *QSettingsSection::groupAt(int index) const
{
	Q_ASSERT_X2(index >= 0 && index < this->grps.size(), "index out of range");
	return this->grps.at(index);
}

int QSettingsSection::groupIndex(QSettingsGroup *group) const
{
	return this->grps.indexOf(group);
}

QSettingsGroup *QSettingsSection::insertGroup(int index, const QString &name, bool optional)
{
	Q_ASSERT_X2(index >= 0 && index <= this->grps.size(), "index out of range");
	QGroupBox *box = new QGroupBox(name, this->contentWidget);
	if(optional) {
		box->setCheckable(true);
		box->setChecked(false);
	}
	QVBoxLayout *layout = static_cast<QVBoxLayout*>(this->contentWidget->layout());
	layout->insertWidget(TEST_DEFAULT(index), box);

	QSettingsGroup *group = new QSettingsGroup(box, this->priv);
	this->grps.insert(index, group);

	return group;
}

void QSettingsSection::deleteGroup(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->grps.size(), "index out of range");
	QVBoxLayout *layout = static_cast<QVBoxLayout*>(this->contentWidget->layout());
	layout->itemAt(TEST_DEFAULT(index))->widget()->deleteLater();
	delete this->grps.takeAt(index);
}

bool QSettingsSection::deleteGroup(QSettingsGroup *group)
{
	int index = this->grps.indexOf(group);
	if(index >= 0) {
		this->deleteGroup(index);
		return true;
	} else
		return false;
}

void QSettingsSection::moveGroup(int from, int to)
{
	Q_ASSERT_X2(from >= 0 && from < this->grps.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to < this->grps.size(), "index out of range");
	QVBoxLayout *layout = static_cast<QVBoxLayout*>(this->contentWidget->layout());
	QLayoutItem *item = layout->takeAt(TEST_DEFAULT(from));
	layout->insertItem(TEST_DEFAULT(to), item);
	this->grps.move(from, to);
}

void QSettingsSection::transferGroup(int from, QSettingsSection *target, int to)
{
	Q_ASSERT_X2(target != this, "you can't transfer a group to it's origin. Use moveGroup instead");
	Q_ASSERT_X2(target->priv == this->priv, "you can't transfer a group to another dialog");
	Q_ASSERT_X2(from >= 0 && from < this->grps.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to <= target->grps.size(), "index out of range");

	QVBoxLayout *thisLayout = static_cast<QVBoxLayout*>(this->contentWidget->layout());
	QWidget *widget = thisLayout->itemAt(TEST_DEFAULT(from))->widget();
	QSettingsGroup *group = this->grps.takeAt(from);

	QVBoxLayout *targetLayout = static_cast<QVBoxLayout*>(target->contentWidget->layout());
	targetLayout->insertWidget(TEST_DEFAULT(to), widget);
	target->grps.insert(to, group);
}

QSettingsGroup *QSettingsSection::defaultGroup()
{
	if(!this->defaultGrp) {
		QWidget *defaultWidget = new QWidget(this->contentWidget);
		QVBoxLayout *layout = static_cast<QVBoxLayout*>(this->contentWidget->layout());
		layout->insertWidget(0, defaultWidget);
		this->defaultGrp = new QSettingsGroup(defaultWidget, this->priv);
	}
	return this->defaultGrp;
}

bool QSettingsSection::hasDefaultGroup() const
{
	return this->defaultGrp;
}
