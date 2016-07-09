#include "qsettingsloader.h"

QSettingsLoader::QSettingsLoader() {}

QSimpleSettingsLoader *QSettingsLoader::simple()
{
	return safe_cast<QSimpleSettingsLoader*>(this);
}

QAsyncSettingsLoader *QSettingsLoader::async()
{
	return safe_cast<QAsyncSettingsLoader*>(this);
}

bool QSimpleSettingsLoader::isAsync() const
{
	return false;
}

bool QAsyncSettingsLoader::isAsync() const
{
	return true;
}

QAsyncSettingsLoader::QAsyncSettingsLoader() :
	QObject(nullptr),
	QSettingsLoader()
{}
