#ifndef SETTINGSENGINE_H
#define SETTINGSENGINE_H

#include <QObject>
#include <QSignalMapper>
#include "qsettingsentry.h"
#include "qsettingsloader.h"
#include "qsettingswidget.h"
#include "checkinghelper.h"

class SettingsEngine : public QObject
{
	Q_OBJECT
public:
	explicit SettingsEngine(QObject *parent = nullptr);

	void addEntry(QSharedPointer<QSettingsEntry> entry,
				  QSettingsWidgetBase *currentWidget,
				  CheckingHelper *checkingHelper);

public slots:
	void startLoading();

signals:
	void progressMaxChanged(int max);
	void progressValueChanged(int value);

	void loadCompleted();

private slots:
	void entryLoaded(const QVariant &data, bool isUserEdited);

private:
	struct EntryInfoBase {
		QSharedPointer<QSettingsEntry> entry;
		QSettingsWidgetBase *currentWidget;
		CheckingHelper *checkingHelper;
	};
	template<class TLoader>
	struct EntryInfo : public EntryInfoBase {
		TLoader *currentLoader;

		inline EntryInfo(QSharedPointer<QSettingsEntry> entry,
				  QSettingsWidgetBase *currentWidget,
				  CheckingHelper *checkingHelper,
				  TLoader *currentLoader) :
			EntryInfoBase({entry, currentWidget, checkingHelper}),
			currentLoader(currentLoader)
		{}
	};

	QList<EntryInfo<QSimpleSettingsLoader>> simpleEntries;
	QList<EntryInfo<QAsyncSettingsLoader>> asyncEntries;

	QHash<QObject*, int> activeAsyncs;
	int currentCount;

	void updateEntry(EntryInfoBase &entry, const QVariant &data, bool isUserEdited);
};

#endif // SETTINGSENGINE_H
