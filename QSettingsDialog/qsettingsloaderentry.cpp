#include "qsettingsloaderentry.h"

QSettingsLoaderEntry::QSettingsLoaderEntry() :
	QSettingsLoader(),
	QSettingsEntry()
{}

QSettingsLoader *QSettingsLoaderEntry::getLoader() const
{
	return const_cast<QSettingsLoaderEntry*>(this);
}
