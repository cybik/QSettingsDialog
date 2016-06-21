#include "commonfactoryregistry.h"

QHash<int, QSharedPointer<QSettingsWidgetFactory>> CommonFactoryRegistry::globalFactories;

CommonFactoryRegistry::CommonFactoryRegistry() :
	factoryMap(globalFactories)
{}

void CommonFactoryRegistry::addGlobalFactory(int id, QSettingsWidgetFactory *factory)
{
	globalFactories.insert(id, QSharedPointer<QSettingsWidgetFactory>(factory));
}

void CommonFactoryRegistry::insertFactory(int id, QSettingsWidgetFactory *factory)
{
	this->factoryMap.insert(id, QSharedPointer<QSettingsWidgetFactory>(factory));
}

QSharedPointer<QSettingsWidgetFactory> CommonFactoryRegistry::tryResolve(int displayId)
{
	return this->factoryMap.value(displayId);
}
