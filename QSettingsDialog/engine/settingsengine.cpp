#include "settingsengine.h"

SettingsEngine::SettingsEngine(QObject *parent) :
	QObject(parent),
	settingsEntries()
{}

void SettingsEngine::addEntry(QSharedPointer<QSettingsEntry> entry, QSettingsWidgetBase *currentWidget)
{
	this->settingsEntries.append({
									 entry,
									 currentWidget,
									 entry->getLoader()
								 });
}

#include <QTimer>
void SettingsEngine::startLoading()
{
	QTimer::singleShot(3000, this, &SettingsEngine::loadCompleted);
}
