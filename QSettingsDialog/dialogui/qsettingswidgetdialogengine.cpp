#include "qsettingswidgetdialogengine.h"
#include "settingsdisplaydialog.h"
#include "settingsenumwidgetfactory.h"
#include "commonfactoryregistry.h"
#include <QMap>

#define d this->d_ptr

class QSettingsWidgetDialogEnginePrivate
{
public:
	static QList<QSharedPointer<QSettingsWidgetFactoryRegistry>> globalRegistries;
	static QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> globalGroupFactories;

	QSharedPointer<CommonFactoryRegistry> commonFactory;
	QMultiMap<int, QSharedPointer<QSettingsWidgetFactoryRegistry>> currentRegistries;
	QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> groupFactories;

	QSettingsWidgetDialogEnginePrivate() :
		commonFactory(new CommonFactoryRegistry()),
		currentRegistries(),
		groupFactories(globalGroupFactories)
	{
		this->currentRegistries.insert(this->commonFactory->priority(), this->commonFactory);
		foreach(auto reg, globalRegistries)
			this->currentRegistries.insert(reg->priority(), reg);
	}
};

QList<QSharedPointer<QSettingsWidgetFactoryRegistry>> QSettingsWidgetDialogEnginePrivate::globalRegistries;
QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> QSettingsWidgetDialogEnginePrivate::globalGroupFactories;

QSettingsWidgetDialogEngine::QSettingsWidgetDialogEngine() :
	d_ptr(new QSettingsWidgetDialogEnginePrivate())
{}

QSettingsWidgetDialogEngine::~QSettingsWidgetDialogEngine() {}

QSettingsDisplayInstance *QSettingsWidgetDialogEngine::createInstance()
{
	return new SettingsDisplayDialog(this);
}

void QSettingsWidgetDialogEngine::addFactory(int displayId, QSettingsWidgetFactory *factory)
{
	d->commonFactory->insertFactory(displayId, factory);
}

void QSettingsWidgetDialogEngine::addGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory)
{
	d->groupFactories.insert(displayId, QSharedPointer<QSettingsGroupWidgetFactory>(factory));
}

QSettingsWidgetBase *QSettingsWidgetDialogEngine::createWidget(int displayId, const QSettingsEntry::UiPropertyMap &properties, QWidget *parent) const
{
	QSettingsWidgetBase *widget = nullptr;

	foreach(auto registry, d->currentRegistries.values()) {
		auto factory = registry->tryResolve(displayId);
		if(factory) {
			widget = factory->createWidget(parent);
			if(widget)
				break;
		}
	}

	if(widget)
		widget->initialize(properties);
	return widget;
}

QSettingsGroupWidgetBase *QSettingsWidgetDialogEngine::createGroupWidget(int displayId, const QSettingsEntry::UiPropertyMap &properties, QWidget *parent) const
{
	auto factory = d->groupFactories.value(displayId);
	if(factory) {
		QSettingsGroupWidgetBase *widget = factory->createGroupWidget(parent);
		if(widget)
			widget->initialize(properties);
		return widget;
	} else
		return nullptr;
}

void QSettingsWidgetDialogEngine::registerGlobalFactory(int displayId, QSettingsWidgetFactory *factory)
{
	CommonFactoryRegistry::addGlobalFactory(displayId, factory);
}

void QSettingsWidgetDialogEngine::registerGlobalGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory)
{
	QSettingsWidgetDialogEnginePrivate::globalGroupFactories.insert(displayId, QSharedPointer<QSettingsGroupWidgetFactory>(factory));
}

void QSettingsWidgetDialogEngine::addRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	d->currentRegistries.insert(registry->priority(), QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}

void QSettingsWidgetDialogEngine::registerGlobalRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	QSettingsWidgetDialogEnginePrivate::globalRegistries.append(QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}
