#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QString>
#include <QIcon>
#include <QSharedPointer>
#include "sortedmap.h"
#include "specialgroupmap.h"
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

	inline SettingsGroup(const QString &name) :
		name(name),
		tooltip(),
		isOptional(false),
		entries()
	{}

	inline void testNotLocked() const {
		if(this->locker != nullptr)
			throw ContainerLockedException();
	}
	inline void testNotLocked(QSettingsContainer *locker) const {
		if(this->locker != nullptr && this->locker != locker)
			throw ContainerLockedException();
	}
};

struct SettingsSection
{
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsGroup> defaultGroup;
	SpecialGroupMap groups;

	inline SettingsSection(const QString &name) :
		name(name),
		icon(),
		tooltip(),
		defaultGroup(),
		groups()
	{}
};

struct SettingsCategory
{
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsSection> defaultSection;
	SortedMap<QString, SettingsSection> sections;

	inline SettingsCategory(const QString &name) :
		name(name),
		icon(),
		tooltip(),
		defaultSection(),
		sections()
	{}
};

struct SettingsRoot
{
	QSharedPointer<SettingsCategory> defaultCategory;
	SortedMap<QString, SettingsCategory> categories;
};

#endif // CONTAINERELEMENT_H
