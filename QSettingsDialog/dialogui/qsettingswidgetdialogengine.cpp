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

	QSharedPointer<CommonFactoryRegistry> commonFactory;
	QMultiMap<int, QSharedPointer<QSettingsWidgetFactoryRegistry>> currentRegistries;

	QSettingsWidgetDialogEnginePrivate() :
		commonFactory(new CommonFactoryRegistry()),
		currentRegistries()
	{
		this->currentRegistries.insert(this->commonFactory->priority(), this->commonFactory);
		foreach(auto reg, globalRegistries)
			this->currentRegistries.insert(reg->priority(), reg);
	}
};

QList<QSharedPointer<QSettingsWidgetFactoryRegistry>> QSettingsWidgetDialogEnginePrivate::globalRegistries;

QSettingsWidgetDialogEngine::QSettingsWidgetDialogEngine() :
	d_ptr(new QSettingsWidgetDialogEnginePrivate())
{}

QSettingsWidgetDialogEngine::~QSettingsWidgetDialogEngine() {}

QSettingsDisplayInstance *QSettingsWidgetDialogEngine::createInstance()
{
	return new SettingsDisplayDialog(this);
}

void QSettingsWidgetDialogEngine::addFactory(int metatype, QSettingsWidgetFactory *factory)
{
	d->commonFactory->insertFactory(metatype, factory);
}

QSettingsWidgetBase *QSettingsWidgetDialogEngine::createWidget(int metatype, const QSettingsEntry::UiPropertyMap &properties, QWidget *parent) const
{
	QSettingsWidgetBase *widget = nullptr;

	foreach(auto registry, d->currentRegistries.values()) {
		auto factory = registry->tryResolve(metatype);
		if(factory) {
			widget = factory->createWidget(parent);
			if(widget)
				break;
		}
	}

	if(widget) {
		auto oWidget = widget->asWidget();
		Q_ASSERT(oWidget);
		for(QSettingsEntry::UiPropertyMap::const_iterator it = properties.constBegin(), end = properties.constEnd(); it != end; ++it)
			oWidget->setProperty(it.key().toLocal8Bit().constData(), it.value());
	}
	return widget;
}

void QSettingsWidgetDialogEngine::registerGlobalFactory(int metatype, QSettingsWidgetFactory *factory)
{
	CommonFactoryRegistry::addGlobalFactory(metatype, factory);
}

void QSettingsWidgetDialogEngine::addRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	d->currentRegistries.insert(registry->priority(), QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}

void QSettingsWidgetDialogEngine::registerGlobalRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	QSettingsWidgetDialogEnginePrivate::globalRegistries.append(QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}
