#include "settingsengine.h"

SettingsEngine::SettingsEngine(QObject *parent) :
	QObject(parent),
	simpleEntries(),
	asyncEntries(),
	activeAsyncs(),
	currentCount(0)
{}

void SettingsEngine::addEntry(QSharedPointer<QSettingsEntry> entry, QSettingsWidgetBase *currentWidget, CheckingHelper *checkingHelper)
{
	auto loader = entry->getLoader();
	if(loader->isAsync()) {
		connect(loader->async(), &QAsyncSettingsLoader::loadDone,
				this, &SettingsEngine::entryLoaded);

		this->asyncEntries.append({
									  entry,
									  currentWidget,
									  checkingHelper,
									  loader->async()
								   });
	} else {
		this->simpleEntries.append({
									   entry,
									   currentWidget,
									   checkingHelper,
									   loader->simple()
								   });
	}
}

void SettingsEngine::startLoading()
{
	for(int i = 0, total = this->asyncEntries.size(); i < total; ++i) {
		EntryInfo<QAsyncSettingsLoader> &entry = this->asyncEntries[i];
		this->activeAsyncs.insert(entry.currentLoader, i);
		QMetaObject::invokeMethod(entry.currentLoader, "loadData", Qt::QueuedConnection);
	}
	this->currentCount = 0;
	emit progressMaxChanged(this->activeAsyncs.size());

	foreach(auto entry, this->simpleEntries) {
		bool edited = false;
		auto data = entry.currentLoader->load(edited);
		this->updateEntry(entry, data, edited);
	}

	if(this->activeAsyncs.isEmpty())
		emit loadCompleted();
}

void SettingsEngine::entryLoaded(const QVariant &data, bool isUserEdited)
{
	if(this->activeAsyncs.contains(QObject::sender())) {
		auto index = this->activeAsyncs.take(QObject::sender());
		EntryInfo<QAsyncSettingsLoader> &entry = this->asyncEntries[index];
		this->updateEntry(entry, data, isUserEdited);
	}

	emit progressValueChanged(++this->currentCount);
	if(this->activeAsyncs.isEmpty())
		emit loadCompleted();
}

void SettingsEngine::updateEntry(EntryInfoBase &entry, const QVariant &data, bool isUserEdited)
{
	if(data.isValid())
		entry.currentWidget->setValue(data);
	else
		entry.currentWidget->resetValue();
	entry.currentWidget->resetValueChanged();

	if(isUserEdited && entry.checkingHelper)
		entry.checkingHelper->doCheck();
}
