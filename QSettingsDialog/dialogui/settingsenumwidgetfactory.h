#ifndef SETTINGSENUMWIDGETFACTORY_H
#define SETTINGSENUMWIDGETFACTORY_H

#include "qsettingswidget.h"
#include <QMetaEnum>
#include <QFlags>

class SettingsEnumWidgetFactory
{
public:
	static QSettingsWidgetBase *createWidget(const QMetaEnum &metaEnum, QWidget *parent);
};

#endif // SETTINGSENUMWIDGETFACTORY_H
