#include "qsettingspropertyentry.h"
#include "qsettingspropertyloader.h"



QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QObject *object) :
	QSettingsEntry(0, new QSettingsPropertyLoader(propertyName, object))
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object) :
	QSettingsEntry(0, new QSettingsPropertyLoader(metaProperty, object))
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget) :
	QSettingsEntry(0, new QSettingsPropertyLoader(propertyName, metaObject, gadget))
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget) :
	QSettingsEntry(0, new QSettingsPropertyLoader(metaProperty, gadget))
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QObject *object, const QString &name, bool optional, const QString &tooltip, const QSettingsEntry::UiPropertyMap &properties) :
	QSettingsEntry(0, new QSettingsPropertyLoader(propertyName, object), name, optional, tooltip, properties)
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object, const QString &name, bool optional, const QString &tooltip, const QSettingsEntry::UiPropertyMap &properties) :
	QSettingsEntry(0, new QSettingsPropertyLoader(metaProperty, object), name, optional, tooltip, properties)
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget, const QString &name, bool optional, const QString &tooltip, const QSettingsEntry::UiPropertyMap &properties) :
	QSettingsEntry(0, new QSettingsPropertyLoader(propertyName, metaObject, gadget), name, optional, tooltip, properties)
{}

QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget, const QString &name, bool optional, const QString &tooltip, const QSettingsEntry::UiPropertyMap &properties) :
	QSettingsEntry(0, new QSettingsPropertyLoader(metaProperty, gadget), name, optional, tooltip, properties)
{}

int QSettingsPropertyEntry::displaytype()
{
	auto loader = safe_cast<QSettingsPropertyLoader*>(this->getLoader());
	auto id = loader->metatypeId();
	this->freeLoader(loader);
	return id;
}
