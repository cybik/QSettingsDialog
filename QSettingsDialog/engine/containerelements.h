#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QList>
#include <QString>
#include <QIcon>
#include <QScopedPointer>
#include <QSharedPointer>

class QSettingsGroup
{
public:
	QString name;
	QString tooltip;
	bool isOptional;
};

class QSettingsSection
{
public:
	QString name;
	QIcon icon;
	QString tooltip;

	QScopedPointer<QSettingsGroup> defaultGroup;
	QList<QSharedPointer<QSettingsGroup>> groups;

private:
	QScopedPointer<QSettingsGroup> defaultGrp;
};

class QSettingsCategory
{
public:
	QString name;
	QIcon icon;
	QString tooltip;

	QScopedPointer<QSettingsSection> defaultSection;
	QList<QSharedPointer<QSettingsSection>> sections;
};

class QSettingsRoot
{
public:
	QScopedPointer<QSettingsCategory> defaultcategory;
	QList<QSharedPointer<QSettingsCategory>> categories;
};

#endif // CONTAINERELEMENT_H
