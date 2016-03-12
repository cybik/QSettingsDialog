#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsloader.h"
#include "qsettingswidget.h"
#include <QWidget>

class QSettingsEntry
{
public:
	inline virtual ~QSettingsEntry() {}

	virtual QString entryName() const = 0;
	virtual bool isOptional() const = 0;

	virtual QSettingsWidgetBase *createWidget(QWidget *parent) = 0;
	virtual inline void destroyWidget(QSettingsWidgetBase *widget) {
		widget->asWidget()->deleteLater();
	}
	virtual QSettingsLoader *getLoader() const = 0;

	template<typename T>
	static inline QVariant asParameter(const T *value) {
		return QVariant::fromValue<void*>(static_cast<void*>(value));
	}

	template<typename T>
	static inline QVariant asParameter(const T &value) {
		return QSettingsEntry::asParameter(new T(value));
	}

	template<typename T>
	static inline T* asValuePtr(const QVariant &parameter) {
		return static_cast<T*>(parameter.value<void*>());
	}

	template<typename T>
	static inline T asValue(const QVariant &parameter) {
		T *vPtr = QSettingsEntry::asValuePtr(parameter);
		T value = *vPtr;
		delete vPtr;
		return value;
	}
};

#endif // QSETTINGSENTRY_H
