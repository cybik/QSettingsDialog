#ifndef QSETTINGSVARIANTENTRY_P_H
#define QSETTINGSVARIANTENTRY_P_H

#include "qsettingsvariantentry.h"
#include "standardSettingsWidgets/settingsenumcombobox.h"

class QSettingsVariantWidgetProvider
{
public:
	static QSettingsVariantWidgetProvider *instance();

	QSettingsVariantWidgetProvider();//internal!!!
	~QSettingsVariantWidgetProvider();

	QSettingsWidgetFactory *getFactory(int type);
	void addFactory(int type, QSettingsWidgetFactory *factory);

private:
	QHash<int, QSettingsWidgetFactory*> factoryMap;
	QSettingsWidgetFactory *fallbackFactory;
	MetaEnumSettingsWidgetFactory *enumFactory;
};

#endif // QSETTINGSVARIANTENTRY_P_H
