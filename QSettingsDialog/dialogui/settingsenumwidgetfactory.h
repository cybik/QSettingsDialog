#ifndef SETTINGSENUMWIDGETFACTORY_H
#define SETTINGSENUMWIDGETFACTORY_H

#include "qsettingswidgetfactoryregistry.h"
#include <QMetaEnum>
#include <QFlags>

class SettingsEnumWidgetFactory : public QSettingsWidgetFactory
{
public:
	SettingsEnumWidgetFactory(const QMetaEnum &metaEnum);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) override;

private:
	QMetaEnum metaEnum;
};

class SettingsEnumWidgetRegistry : public QSettingsWidgetFactoryRegistry
{
public:
	// QSettingsWidgetFactoryRegistry interface
	int priority() const override;
	QSharedPointer<QSettingsWidgetFactory> tryResolve(int displayId) override;
};

#endif // SETTINGSENUMWIDGETFACTORY_H
