#ifndef COMMONFACTORYREGISTRY_H
#define COMMONFACTORYREGISTRY_H

#include "qsettingswidgetfactoryregistry.h"

class CommonFactoryRegistry : public QSettingsWidgetFactoryRegistry
{
public:
	CommonFactoryRegistry();

	static void addGlobalFactory(int id, QSettingsWidgetFactory *factory);

	void insertFactory(int id, QSettingsWidgetFactory *factory);
	QSharedPointer<QSettingsWidgetFactory> tryResolve(int displayId) override;

private:
	static QHash<int, QSharedPointer<QSettingsWidgetFactory>> globalFactories;

	QHash<int, QSharedPointer<QSettingsWidgetFactory>> factoryMap;
};



#endif // COMMONFACTORYREGISTRY_H
