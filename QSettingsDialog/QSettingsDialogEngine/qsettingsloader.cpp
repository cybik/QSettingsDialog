#include "qsettingsloader.h"

QSettingsLoader::QSettingsLoader(QObject *parent) :
	QObject(parent)
{}



QSimpleSettingsLoader::QSimpleSettingsLoader(QObject *parent):
	QSettingsLoader(parent)
{}

void QSimpleSettingsLoader::loadData()
{
	bool userEdited = false;
	auto data = this->load(userEdited);
	emit loadDone(data, userEdited);
}

void QSimpleSettingsLoader::saveData(const QVariant &data)
{
	emit saveDone(this->save(data));
}

void QSimpleSettingsLoader::resetData()
{
	emit resetDone(this->reset());
}
