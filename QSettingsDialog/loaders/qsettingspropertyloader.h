#ifndef QSETTINGSPROPERTYLOADER_H
#define QSETTINGSPROPERTYLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QMetaProperty>
#include <QScopedPointer>
#include "qsettingsloader.h"

class QSettingsPropertyLoaderPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsPropertyLoader : public QAsyncSettingsLoader
{
	Q_OBJECT

public:
	explicit QSettingsPropertyLoader(const char *propertyName, QObject *object);
	explicit QSettingsPropertyLoader(const QMetaProperty &metaProperty, QObject *object);
	explicit QSettingsPropertyLoader(const char *propertyName, QMetaObject *metaObject, void *gadget);
	explicit QSettingsPropertyLoader(const QMetaProperty &metaProperty, void *gadget);
	~QSettingsPropertyLoader();

	int metatypeId() const;
	bool isValid() const;

public slots:	
	// QAsyncSettingsLoader interface
	void loadData() override;
	void saveData(const QVariant &data) override;
	void resetData() override;

private:
	QScopedPointer<QSettingsPropertyLoaderPrivate> d_ptr;
};

#endif // QSETTINGSPROPERTYLOADER_H
