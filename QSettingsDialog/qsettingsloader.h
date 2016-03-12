#ifndef QSETTINGSLOADER_H
#define QSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include <QObject>

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

#endif // QSETTINGSLOADER_H
