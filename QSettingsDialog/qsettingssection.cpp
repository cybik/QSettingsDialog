#include "qsettingssection.h"
#include <QTabBar>

QSettingsSection::QSettingsSection(QTabBar *tabBar, int tabIndex, QWidget *contentWidget) :
	tabBar(tabBar),
	tabIndex(tabIndex),
	contentWidget(contentWidget),
	defaultGrp(Q_NULLPTR),
	grps()
{}

QSettingsSection::~QSettingsSection()
{
	delete this->defaultGrp;
	qDeleteAll(this->grps);
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

QSettingsGroup *QSettingsSection::groupAt(int index) const
{
	Q_ASSERT_X2(index >= 0 && index < this->grps.size(), "index out of range");
	return this->grps.at(index);
}

int QSettingsSection::groupIndex(QSettingsGroup *group) const
{
	return this->grps.indexOf(group);
}

QSettingsGroup *QSettingsSection::insertGroup(int index, const QString &name)
{
	Q_ASSERT_X2(index >= 0 && index <= this->grps.size(), "index out of range");
	//TODO
	return Q_NULLPTR;
}

void QSettingsSection::deleteGroup(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->grps.size(), "index out of range");
	//TODO
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
	this->grps.move(from, to);
	//TODO
}

QSettingsGroup *QSettingsSection::defaultGroup()
{
	return this->defaultGrp;
}
