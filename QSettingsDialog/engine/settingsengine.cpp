#include "settingsengine.h"

SettingsEngine::SettingsEngine(QObject *parent) :
	QObject(parent),
	simpleEntries(),
	asyncEntries(),
	activeAsyncs()
{}

void SettingsEngine::addEntry(QSharedPointer<QSettingsEntry> entry, QSettingsWidgetBase *currentWidget)
{
	auto loader = entry->getLoader();
	if(loader->isAsync()) {
		this->asyncEntries.append({
									  entry,
									  currentWidget,
									  loader->async()
								   });
	} else {
		this->simpleEntries.append({
									   entry,
									   currentWidget,
									   loader->simple()
								   });
	}
}

void SettingsEngine::startLoading()
{
	foreach(auto entry, this->simpleEntries) {
		bool edited = false;
		auto data = entry.currentLoader->load(edited);
		entry.currentWidget->setValue(data);
		entry.currentWidget->resetValueChanged();
		//TODO toggle checkbox
	}

	for(int i = 0, total = this->asyncEntries.size(); i < total; ++i) {
		EntryInfo<QAsyncSettingsLoader> &entry = this->asyncEntries[i];
		//HERE
	}
}
