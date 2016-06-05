#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QString>
#include <QIcon>
#include <QSharedPointer>
#include <QMutex>
#include "sortedmap.h"
#include "qsettingsentry.h"

struct SettingsGroup
{
	QMutex lock;

	QString name;
	QString tooltip;
	bool isOptional;

	SortedMap<int, QSettingsEntry> entries;
};

struct SettingsSection
{
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsGroup> defaultGroup;
	SortedMap<QString, SettingsGroup> groups;
};

struct SettingsCategory
{
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsSection> defaultSection;
	SortedMap<QString, SettingsSection> sections;
};

struct SettingsRoot
{
	QSharedPointer<SettingsCategory> defaultCategory;
	SortedMap<QString, SettingsCategory> categories;
};

#endif // CONTAINERELEMENT_H
