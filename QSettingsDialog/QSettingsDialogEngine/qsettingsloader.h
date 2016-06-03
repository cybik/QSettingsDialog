#ifndef QSETTINGSLOADER_H
#define QSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QVariant>

class QSimpleSettingsLoader;
class QAsyncSettingsLoader;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsLoader
{
public:
	virtual inline ~QSettingsLoader() {}
	virtual bool isAsync() const = 0;

	QSimpleSettingsLoader *simple();
	QAsyncSettingsLoader *async();
};

class QSETTINGSDIALOGSHARED_EXPORT QSimpleSettingsLoader : public QSettingsLoader
{
public:
	bool isAsync() const final;

	virtual QVariant load(bool outParam userEdited) = 0;
	virtual bool save(const QVariant &data) = 0;
	virtual bool reset() = 0;
};

class QSETTINGSDIALOGSHARED_EXPORT QAsyncSettingsLoader : public QObject, public QSettingsLoader
{
	Q_OBJECT

public:
	QAsyncSettingsLoader(QObject *parent = nullptr);

	bool isAsync() const final;

public slots:
	virtual void loadData() = 0;
	virtual void saveData(const QVariant &data) = 0;
	virtual void resetData() = 0;

signals:
	void loadDone(const QVariant &data, bool isUserEdited = true);
	void saveDone(bool successfull);
	void resetDone(bool successfull);
};

#endif // QSETTINGSLOADER_H
