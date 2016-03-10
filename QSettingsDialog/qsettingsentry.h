#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsloader.h"

class QSettingsEntry
{
public:
	virtual inline ~QSettingsEntry() {}

	virtual QString entryName() const = 0;
	virtual bool isOptional() const = 0;

	virtual QWidget *createWidget(QWidget *parent) = 0;
	virtual QSettingsLoader *createLoader() = 0;

	virtual void setValue(QWidget *widget, const QVariant &value) = 0;
	virtual QVariant getValue(QWidget *widget) = 0;
	virtual void resetWidget(QWidget *widget) = 0;

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
