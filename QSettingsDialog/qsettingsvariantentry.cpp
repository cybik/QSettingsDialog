#include "qsettingsvariantentry.h"
#include "qsettingsvariantentry_p.h"
#include <QGlobalStatic>

#include "standardSettingsWidgets/settingslineedit.h"
#include "standardSettingsWidgets/settingscheckbox.h"
#include "standardSettingsWidgets/settingsspinbox.h"

QSettingsVariantEntry::QSettingsVariantEntry(const QString &entryName, bool isOptional, QSettingsVariantLoader *loader) :
	QSettingsEntry(),
	name(entryName),
	optional(isOptional),
	loader(loader)
{}

QString QSettingsVariantEntry::entryName() const
{
	return this->name;
}

bool QSettingsVariantEntry::isOptional() const
{
	return this->optional;
}

QSettingsWidgetBase *QSettingsVariantEntry::createWidget(QWidget *parent)
{
	QSettingsWidgetBase *setWid;
	setWid = QSettingsVariantWidgetProvider::instance()->getFactory(this->loader->variantTypeID())->createWidget(parent);

	QSettingsVariantLoader::PropertyMap properties = this->loader->widgetProperties();
	QWidget *widget = setWid->asWidget();
	for(QSettingsVariantLoader::PropertyMap::const_iterator it = properties.constBegin(),
															end = properties.constEnd();
		it != end;
		++it) {
		widget->setProperty(it.key().toLocal8Bit().constData(), it.value());
	}

	return setWid;
}

void QSettingsVariantEntry::destroyWidget(QSettingsWidgetBase *widget)
{
	QSettingsVariantWidgetProvider::instance()->getFactory(this->loader->variantTypeID())->destroyWidget(widget);
}

QSettingsLoader *QSettingsVariantEntry::getLoader() const
{
	return this->loader;
}

void QSettingsVariantEntry::registerWidgetFactory(int variantType, QSettingsWidgetFactory *factory)
{
	QSettingsVariantWidgetProvider::instance()->addFactory(variantType, factory);
}

//----------------------- PRIVATE IMPLEMENTATION -----------------------

Q_GLOBAL_STATIC(QSettingsVariantWidgetProvider, provider)

QSettingsVariantWidgetProvider *QSettingsVariantWidgetProvider::instance()
{
	return provider;
}

QSettingsVariantWidgetProvider::QSettingsVariantWidgetProvider() :
	factoryMap(),
	fallbackFactory(new GenericSettingsWidgetFactory<SettingsLineEdit>())
{
	this->factoryMap.insert(QMetaType::Bool, new GenericSettingsWidgetFactory<SettingsCheckBox>());
	this->factoryMap.insert(QMetaType::Int, new SpinBoxFactory());
	this->factoryMap.insert(QMetaType::UInt, new SpinBoxFactory(INT_MAX, 0));

	this->factoryMap.insert(QMetaType::QString, new GenericSettingsWidgetFactory<SettingsLineEdit>());
	this->factoryMap.insert(QMetaType::QByteArray, new GenericSettingsWidgetFactory<SettingsLineEdit>());
}

QSettingsVariantWidgetProvider::~QSettingsVariantWidgetProvider()
{
	qDeleteAll(this->factoryMap.values());
	delete this->fallbackFactory;
}

QSettingsWidgetFactory *QSettingsVariantWidgetProvider::getFactory(int type)
{
	return this->factoryMap.value(type, this->fallbackFactory);
}

void QSettingsVariantWidgetProvider::addFactory(int type, QSettingsWidgetFactory *factory)
{
	delete this->factoryMap.take(type);
	this->factoryMap.insert(type, factory);
}
