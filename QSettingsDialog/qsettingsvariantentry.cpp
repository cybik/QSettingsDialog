#include "qsettingsvariantentry.h"
#include "qsettingsvariantentry_p.h"
#include <QGlobalStatic>

#include "standardSettingsWidgets/settingslineedit.h"
#include "standardSettingsWidgets/settingscheckbox.h"
#include "standardSettingsWidgets/settingsspinbox.h"
#include "standardSettingsWidgets/settingsdatetimeedit.h"
#include "standardSettingsWidgets/settingscoloredit.h"
#include "standardSettingsWidgets/settingslistedit.h"
#include "standardSettingsWidgets/settingsfontcombobox.h"

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
	fallbackFactory(new GenericSettingsWidgetFactory<SettingsLineEdit>()),
	enumFactory(new MetaEnumSettingsWidgetFactory())
{
	this->factoryMap.insert(QMetaType::Bool, new GenericSettingsWidgetFactory<SettingsCheckBox>());
	this->factoryMap.insert(QMetaType::Int, new SpinBoxFactory());
	this->factoryMap.insert(QMetaType::UInt, new SpinBoxFactory(INT_MAX, 0));
	this->factoryMap.insert(QMetaType::Double, new DoubleSpinBoxFactory());
	this->factoryMap.insert(QMetaType::QString, new GenericSettingsWidgetFactory<SettingsLineEdit>());
	this->factoryMap.insert(QMetaType::QByteArray, new GenericSettingsWidgetFactory<SettingsLineEdit>());
	this->factoryMap.insert(QMetaType::Long, new SpinBoxFactory(LONG_MAX, LONG_MIN));
	this->factoryMap.insert(QMetaType::LongLong, new SpinBoxFactory(LONG_MAX, LONG_MIN));
	this->factoryMap.insert(QMetaType::Short, new SpinBoxFactory(SHRT_MAX, SHRT_MIN));
	this->factoryMap.insert(QMetaType::Char, new SpinBoxFactory(CHAR_MAX, CHAR_MIN));
	this->factoryMap.insert(QMetaType::ULong, new SpinBoxFactory(LONG_MAX, 0));
	this->factoryMap.insert(QMetaType::ULongLong, new SpinBoxFactory(LONG_MAX, 0));
	this->factoryMap.insert(QMetaType::UShort, new SpinBoxFactory(USHRT_MAX, 0));
	this->factoryMap.insert(QMetaType::SChar, new SpinBoxFactory(CHAR_MAX, CHAR_MIN));
	this->factoryMap.insert(QMetaType::UChar, new SpinBoxFactory(UCHAR_MAX, 0));
	this->factoryMap.insert(QMetaType::Float, new DoubleSpinBoxFactory(FLT_MAX, FLT_MIN));
	this->factoryMap.insert(QMetaType::QDate, new GenericSettingsWidgetFactory<SettingsDateEdit>());
	this->factoryMap.insert(QMetaType::QTime, new GenericSettingsWidgetFactory<SettingsTimeEdit>());
	this->factoryMap.insert(QMetaType::QColor, new GenericSettingsWidgetFactory<SettingsColorEdit>());
	this->factoryMap.insert(QMetaType::QStringList, new GenericSettingsWidgetFactory<SettingsListEditWidget>());
	this->factoryMap.insert(QMetaType::QUrl, new GenericSettingsWidgetFactory<SettingsUrlLineEdit>());
	this->factoryMap.insert(QMetaType::QDateTime, new GenericSettingsWidgetFactory<SettingsDateTimeEdit>());
	this->factoryMap.insert(QMetaType::QFont, new GenericSettingsWidgetFactory<SettingsFontComboBox>());
	this->factoryMap.insert(QMetaType::QByteArrayList, new GenericSettingsWidgetFactory<SettingsListEditWidget>());
}

QSettingsVariantWidgetProvider::~QSettingsVariantWidgetProvider()
{
	qDeleteAll(this->factoryMap.values());
	delete this->fallbackFactory;
	delete this->enumFactory;
}

QSettingsWidgetFactory *QSettingsVariantWidgetProvider::getFactory(int type)
{
	QSettingsWidgetFactory *factory = this->factoryMap.value(type, Q_NULLPTR);
	if(factory)
		return factory;
	else if(this->enumFactory->prepareForEnum(type))
		return this->enumFactory;
	else
		return this->fallbackFactory;
}

void QSettingsVariantWidgetProvider::addFactory(int type, QSettingsWidgetFactory *factory)
{
	delete this->factoryMap.take(type);
	this->factoryMap.insert(type, factory);
}
