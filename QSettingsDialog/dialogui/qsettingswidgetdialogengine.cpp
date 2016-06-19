#include "qsettingswidgetdialogengine.h"
#include "settingsdisplaydialog.h"
#include <QHash>

#define d this->d_ptr

class QSettingsWidgetDialogEnginePrivate
{
public:
	static QHash<int, QSharedPointer<QSettingsWidgetFactory>> globalFactories;

	QHash<int, QSharedPointer<QSettingsWidgetFactory>> factoryMap;

	QSettingsWidgetDialogEnginePrivate() :
		factoryMap(globalFactories)
	{}
};

QHash<int, QSharedPointer<QSettingsWidgetFactory>> QSettingsWidgetDialogEnginePrivate::globalFactories;

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
	d->factoryMap.insert(metatype, QSharedPointer<QSettingsWidgetFactory>(factory));
}

QSettingsWidgetBase *QSettingsWidgetDialogEngine::createWidget(int metatype, const QSettingsEntry::UiPropertyMap &properties, QWidget *parent) const
{
	auto factory = d->factoryMap.value(metatype);
	if(factory) {
		auto widget = factory->createWidget(parent);
		if(widget) {
			auto oWidget = widget->asWidget();
			Q_ASSERT(oWidget);
			for(QSettingsEntry::UiPropertyMap::const_iterator it = properties.constBegin(), end = properties.constEnd(); it != end; ++it)
				oWidget->setProperty(it.key().toLocal8Bit().constData(), it.value());
		}
		return widget;
	}
	else
		return nullptr;
}

void QSettingsWidgetDialogEngine::registerGlobalFactory(int metatype, QSettingsWidgetFactory *factory)
{
	QSettingsWidgetDialogEnginePrivate::globalFactories.insert(metatype, QSharedPointer<QSettingsWidgetFactory>(factory));
}
