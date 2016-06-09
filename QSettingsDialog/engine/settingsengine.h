#ifndef SETTINGSENGINE_H
#define SETTINGSENGINE_H

#include <QObject>
#include <QSignalMapper>
#include "qsettingsentry.h"
#include "qsettingsloader.h"
#include "qsettingswidget.h"

class SettingsEngine : public QObject
{
	Q_OBJECT
public:
	explicit SettingsEngine(QObject *parent = nullptr);

	void addEntry(QSharedPointer<QSettingsEntry> entry, QSettingsWidgetBase *currentWidget);

public slots:
	void startLoading();

signals:
	void progressMaxChanged(int max);
	void progressValueChanged(int value);

	void loadCompleted();

private slots:
	void entryLoaded

private:
	template<class TLoader>
	struct EntryInfo {
		QSharedPointer<QSettingsEntry> entry;
		QSettingsWidgetBase *currentWidget;
		TLoader *currentLoader;
	};

	QList<EntryInfo<QSimpleSettingsLoader>> simpleEntries;
	QList<EntryInfo<QAsyncSettingsLoader>> asyncEntries;

	QHash<QObject, int> activeAsyncs;
};

#endif // SETTINGSENGINE_H
