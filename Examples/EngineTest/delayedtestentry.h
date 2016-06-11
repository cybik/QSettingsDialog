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
	explicit DelayedTestEntry(QVariant data, int delayMSecs, QObject *parent = nullptr);

	// QSettingsEntry interface
public:
	QString entryName() const override;
	bool isOptional() const override;
	QString tooltip() const override;
	QSettingsWidgetBase *createWidget(QWidget *parent) override;
	QSettingsLoader *getLoader() override;
	void freeLoader(QSettingsLoader *loader) override;

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
