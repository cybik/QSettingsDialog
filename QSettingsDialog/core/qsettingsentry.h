#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include <QScopedPointer>
#include <QHash>
#include "qsettingsloader.h"

class QSettingsEntryPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsEntry
{
public:
	typedef QHash<QString, QVariant> UiPropertyMap;

	QSettingsEntry(int displaytype, QSettingsLoader *loader);
	QSettingsEntry(int displaytype,
				   QSettingsLoader *loader,
				   const QString &name,
				   bool optional = false,
				   const QString &tooltip = QString(),
				   const UiPropertyMap &properties = UiPropertyMap());
	template<typename... Args>
	QSettingsEntry(int displaytype,
				   QSettingsLoader *loader,
				   const QString &name,
				   bool optional,
				   const QString &tooltip,
				   Args... properties);
	virtual ~QSettingsEntry();

	QString entryName() const;
	void setEntryName(const QString &name);
	bool isOptional() const;
	void setOptional(bool optional);
	QString tooltip() const;
	void setTooltip(const QString &tooltip);

	UiPropertyMap uiProperties() const;
	void setUiProperties(const UiPropertyMap &properties);
	void setUiProperty(const QString &name, const QVariant &value);

	virtual int displaytype() const;
	virtual QSettingsLoader *getLoader();
	virtual void freeLoader(QSettingsLoader *loader);

private:
	QScopedPointer<QSettingsEntryPrivate> d_ptr;
};



template<typename TVariant>
QSettingsEntry::UiPropertyMap mapWrapper(const char *key, TVariant value) {
	return QSettingsEntry::UiPropertyMap({{key, QVariant::fromValue(value)}});
}

template<typename TVariant, typename... Args>
QSettingsEntry::UiPropertyMap mapWrapper(const char *key, TVariant value, Args... params) {
	auto map = mapWrapper(params...);
	map.insert(key, QVariant::fromValue(value));
	return map;
}

template<typename... Args>
QSettingsEntry::QSettingsEntry(int metatype, QSettingsLoader *loader, const QString &name, bool optional, const QString &tooltip, Args... properties) :
	QSettingsEntry(metatype, loader, name, optional, tooltip, mapWrapper(properties...))
{}

#endif // QSETTINGSENTRY_H
