#ifndef TYPELOADER_H
#define TYPELOADER_H

#include <qsettingsvariantentry.h>
#include <QMetaType>

template <typename T>
class TypeLoader : public QSettingsVariantLoader
{
public:
	TypeLoader(const T &value = T()) :
		value(value),
		defaultValue(value),
		changed(false)
	{}

	int variantTypeID() const Q_DECL_OVERRIDE {
		return qMetaTypeId<T>();
	}

public slots:
	void loadData() Q_DECL_OVERRIDE {
		emit loadDone(QVariant::fromValue<T>(value), changed);
	}
	void saveData(const QVariant &data) Q_DECL_OVERRIDE {
		this->value = data.value<T>();
		this->changed = true;
		emit saveDone(true);
	}
	void resetData() Q_DECL_OVERRIDE {
		this->value = defaultValue;
		this->changed = false;
		emit resetDone(true);
	}

private:
	T value;
	T defaultValue;
	bool changed;
};

#endif // TYPELOADER_H
