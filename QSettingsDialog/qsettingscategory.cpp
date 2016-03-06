#include "qsettingscategory.h"
#include <QListWidgetItem>
#include <QTabWidget>

QSettingsCategory::QSettingsCategory(QListWidgetItem *listEntry, QTabWidget *contentWidget) :
	listEntry(listEntry),
	contentWidget(contentWidget),
	defaultSect(Q_NULLPTR),//TODO
	sects()
{}

QSettingsCategory::~QSettingsCategory()
{
	delete this->defaultSect;
	qDeleteAll(this->sects);
}

QString QSettingsCategory::name() const
{
	return this->listEntry->text();
}

QIcon QSettingsCategory::icon() const
{
	return this->listEntry->icon();
}

QString QSettingsCategory::toolTip() const
{
	return this->listEntry->toolTip();
}

void QSettingsCategory::setName(const QString &name)
{
	this->listEntry->setText(name);
}

void QSettingsCategory::setIcon(const QIcon &icon)
{
	this->listEntry->setIcon(icon);
}

void QSettingsCategory::setToolTip(const QString &toolTip)
{
	this->listEntry->setToolTip(toolTip);
}

QSettingsSection *QSettingsCategory::defaultSection() const
{
	return this->defaultSect;
}

QList<QSettingsSection *> QSettingsCategory::sections(bool includeDefault) const
{
	QList<QSettingsSection *> sections = this->sects;
	if(includeDefault)
		sections.prepend(this->defaultSect);
	return sections;
}

QSettingsSection *QSettingsCategory::sectionAt(int index) const
{
	Q_ASSERT_X2(index >= 0 && index < this->sects.size(), "index out of range");
	return this->sects.at(index);
}

int QSettingsCategory::sectionIndex(QSettingsSection *section) const
{
	return this->sects.indexOf(section);
}

QSettingsSection *QSettingsCategory::insertSection(int index, const QString &name, const QIcon &icon)
{
	Q_ASSERT_X2(index >= 0 && index <= this->sects.size(), "index out of range");
	//TODO
	return Q_NULLPTR;
}

void QSettingsCategory::deleteSection(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->sects.size(), "index out of range");
	//TODO
	delete this->sects.takeAt(index);
}

bool QSettingsCategory::deleteSection(QSettingsSection *section)
{
	int index = this->sects.indexOf(section);
	if(index >= 0) {
		this->deleteSection(index);
		return true;
	} else
		return false;
}

void QSettingsCategory::moveSection(int from, int to)
{
	Q_ASSERT_X2(from >= 0 && from < this->sects.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to < this->sects.size(), "index out of range");
	this->sects.move(from, to);
	//TODO
}

QSettingsGroup *QSettingsCategory::defaultGroup() const
{
	//TODO
	return Q_NULLPTR;
}
