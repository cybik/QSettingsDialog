#include "qsettingswidgetdialogengine.h"
#include "settingsdisplaydialog.h"
#include "settingsenumwidgetfactory.h"
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
	QSettingsWidgetBase *widget = nullptr;

	auto factory = d->factoryMap.value(metatype);
	if(factory)
		widget = factory->createWidget(parent);
	else {//if(QMetaType(metatype).flags().testFlag(QMetaType::IsEnumeration)) {
		auto metaObject = QMetaType::metaObjectForType(metatype);
		if(metaObject) {
			QStringList metaNameList = QString::fromLocal8Bit(QMetaType::typeName(metatype)).split(QStringLiteral("::"));
			int index = -1;
			QString testName = metaNameList.takeLast();
			forever {
				index = metaObject->indexOfEnumerator(testName.toLocal8Bit().constData());
				if(index >= 0)
					break;
				else if(metaNameList.isEmpty())
					break;
				else
					testName = testName.prepend(metaNameList.takeLast() + QStringLiteral("::"));
			}

			auto metaEnum = metaObject->enumerator(index);
			if(metaEnum.isValid())
				widget = SettingsEnumWidgetFactory::createWidget(metaEnum, parent);
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
	QSettingsWidgetDialogEnginePrivate::globalFactories.insert(metatype, QSharedPointer<QSettingsWidgetFactory>(factory));
}
