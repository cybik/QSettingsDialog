#ifndef QSETTINGSLOADER_H
#define QSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QVariant>

class QSETTINGSDIALOGSHARED_EXPORT QSettingsLoader : public QObject
{
	Q_OBJECT
public:
	QSettingsLoader(QObject *parent = Q_NULLPTR);

public slots:
	virtual void loadData() = 0;
	virtual void saveData(const QVariant &data) = 0;
	virtual void resetData() = 0;

signals:
	void loadDone(const QVariant &data, bool isUserEdited = true);
	void saveDone(bool successfull);
	void resetDone(bool successfull);
};

class QSETTINGSDIALOGSHARED_EXPORT QSimpleSettingsLoader : public QSettingsLoader
{
	Q_OBJECT
public:
	QSimpleSettingsLoader(QObject *parent = Q_NULLPTR);

	virtual QVariant load(bool /*out*/ &userEdited) = 0;
	virtual bool save(const QVariant &data) = 0;
	virtual bool reset() = 0;

public slots:
	void loadData() final;
	void saveData(const QVariant &data) final;
	void resetData() final;
};

#endif // QSETTINGSLOADER_H
