#ifndef QSETTINGSPROPERTYENTRY_H
#define QSETTINGSPROPERTYENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
class QSettingsPropertyLoader;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsPropertyEntry : public QSettingsEntry
{
public:
	explicit QSettingsPropertyEntry(const char *propertyName, QObject *object);
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object);
	explicit QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget);
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget);

	explicit QSettingsPropertyEntry(const char *propertyName,
									QObject *object,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									QObject *object,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	explicit QSettingsPropertyEntry(const char *propertyName,
									QMetaObject *metaObject,
									void *gadget,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									void *gadget,
									const QString &name,
									bool optional = false,
									const QString &tooltip = QString(),
									const UiPropertyMap &properties = UiPropertyMap());

	template<typename... Args>
	explicit QSettingsPropertyEntry(const char *propertyName,
									QObject *object,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	template<typename... Args>
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									QObject *object,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	template<typename... Args>
	explicit QSettingsPropertyEntry(const char *propertyName,
									QMetaObject *metaObject,
									void *gadget,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);
	template<typename... Args>
	explicit QSettingsPropertyEntry(const QMetaProperty &metaProperty,
									void *gadget,
									const QString &name,
									bool optional,
									const QString &tooltip,
									Args... properties);

	int displaytype() override;
};


template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QObject *object, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsPropertyEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, QObject *object, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsPropertyEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const char *propertyName, QMetaObject *metaObject, void *gadget, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsPropertyEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

template<typename... Args>
QSettingsPropertyEntry::QSettingsPropertyEntry(const QMetaProperty &metaProperty, void *gadget, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsPropertyEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

#endif // QSETTINGSPROPERTYENTRY_H
