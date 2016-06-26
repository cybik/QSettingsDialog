#ifndef DELAYEDTESTENTRY_H
#define DELAYEDTESTENTRY_H

#include <QObject>
#include <qsettingsloader.h>
#include <qsettingswidget.h>
#include <qsettingsentry.h>

class DelayedTestEntry : public QAsyncSettingsLoader, public QSettingsEntry
{
	Q_OBJECT
public:
	explicit DelayedTestEntry(QVariant data, int delayMSecs);

	// QSettingsEntry interface
public:
	QSettingsLoader *getLoader() final;
	void freeLoader(QSettingsLoader *loader) final;

	// QAsyncSettingsLoader interface
public slots:
	void loadData() override;
	void saveData(const QVariant &data) override;
	void resetData() override;

private:
	QVariant data;
	int delayMSecs;
};

#endif // DELAYEDTESTENTRY_H
