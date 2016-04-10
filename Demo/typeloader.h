#ifndef TYPELOADER_H
#define TYPELOADER_H

#include <qsettingsvariantentry.h>
#include <QMetaType>

template <typename T>
class TypeLoader : public QSettingsVariantLoader
{
public:
	TypeLoader(const T &value = T(), const PropertyMap &properties = PropertyMap()) :
		value(value),
		defaultValue(value),
		properties(properties),
		changed(false)
	{}

	int variantTypeID() const Q_DECL_OVERRIDE {
		return qMetaTypeId<T>();
	}

	PropertyMap widgetProperties() const Q_DECL_OVERRIDE {
		return this->properties;
	}

public slots:
	void loadData() Q_DECL_OVERRIDE {
		emit loadDone(QVariant::fromValue<T>(value), changed);
	}
	void saveData(const QVariant &data) Q_DECL_OVERRIDE {
		this->value = data.value<T>();
		this->changed = true;
		qDebug() << "SAVE:  " << QMetaType::typeName(qMetaTypeId<T>()) << data;
		emit saveDone(true);
	}
	void resetData() Q_DECL_OVERRIDE {
		this->value = defaultValue;
		this->changed = false;
		qDebug() << "RESET: " << QMetaType::typeName(qMetaTypeId<T>());
		emit resetDone(true);
	}

private:
	T value;
	T defaultValue;
	PropertyMap properties;
	bool changed;
};

#endif // TYPELOADER_H
