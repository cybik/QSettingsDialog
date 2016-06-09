#ifndef SETTINGSENGINE_H
#define SETTINGSENGINE_H

#include <QObject>
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

private:
	struct EntryInfo {
		QSharedPointer<QSettingsEntry> entry;
		QSettingsWidgetBase *currentWidget;
		QSettingsLoader *currentLoader;
	};

	QList<EntryInfo> settingsEntries;
};

#endif // SETTINGSENGINE_H
