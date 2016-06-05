#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QString>
#include <QIcon>
#include <QSharedPointer>
#include "sortedmap.h"
#include "qsettingsentry.h"
#include "exceptions.h"
#include <QAtomicPointer>

class QSettingsContainer;
struct SettingsGroup
{
	QAtomicPointer<QSettingsContainer> locker;

	QString name;
	QString tooltip;
	bool isOptional;

	SortedMap<int, QSettingsEntry> entries;

	inline void testNotLocked() const {
		if(this->locker != nullptr)
			throw ContainerLockedException();
	}
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
