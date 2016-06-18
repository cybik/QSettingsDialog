#ifndef QSETTINGSLOADERENTRY_H
#define QSETTINGSLOADERENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
#include "qsettingsloader.h"

class QSettingsLoaderEntry : public QSettingsEntry, public QSimpleSettingsLoader
{
public:
	inline QSettingsLoaderEntry(int metatype) :
		QSettingsEntry(metatype, nullptr)
	{}

	inline QSettingsLoader *getLoader() final {
		return this;
	}
	inline void freeLoader(QSettingsLoader *) final {}
};

#endif // QSETTINGSLOADERENTRY_H
