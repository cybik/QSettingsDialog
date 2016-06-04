#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QList>
#include <QHash>
#include <QString>
#include <QIcon>
#include <QSharedPointer>
#include "qsettingsentry.h"

class SettingsGroup
{
public:
	QString name;
	QString tooltip;
	bool isOptional;

	QHash<int, QSharedPointer<QSettingsEntry>> entries;
	QList<int> entryOrder;
};

class SettingsSection
{
public:
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsGroup> defaultGroup;
	QHash<QString, QSharedPointer<SettingsGroup>> groups;
	QStringList groupOrder;

private:
	QScopedPointer<SettingsGroup> defaultGrp;
};

class SettingsCategory
{
public:
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsSection> defaultSection;
	QHash<QString, QSharedPointer<SettingsSection>> sections;
	QStringList sectionOrder;
};

class SettingsRoot
{
public:
	QSharedPointer<SettingsCategory> defaultcategory;
	QHash<QString, QSharedPointer<SettingsCategory>> categories;
	QStringList categoryOrder;
};

#endif // CONTAINERELEMENT_H
