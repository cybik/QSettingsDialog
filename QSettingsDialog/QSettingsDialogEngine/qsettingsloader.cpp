#include "qsettingsloader.h"

bool QSimpleSettingsLoader::isAsync() const
{
	return false;
}

bool QAsyncSettingsLoader::isAsync() const
{
	return true;
}

QAsyncSettingsLoader::QAsyncSettingsLoader(QObject *parent) :
	QObject(parent),
	QSettingsLoader()
{}

QSimpleSettingsLoader *QSettingsLoader::simple()
{
	Q_ASSERT_X(dynamic_cast<QSimpleSettingsLoader*>(this), Q_FUNC_INFO, "Can't cast to QSimpleSettingsLoader");
	return static_cast<QSimpleSettingsLoader*>(this);
}

QAsyncSettingsLoader *QSettingsLoader::async()
{
	Q_ASSERT_X(dynamic_cast<QAsyncSettingsLoader*>(this), Q_FUNC_INFO, "Can't cast to QSimpleSettingsLoader");
	return static_cast<QAsyncSettingsLoader*>(this);
}
