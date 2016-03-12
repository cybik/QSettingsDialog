#ifndef QSETTINGSLOADERENTRY_H
#define QSETTINGSLOADERENTRY_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsLoaderEntry : public QSettingsLoader, public QSettingsEntry
{
public:
	QSettingsLoaderEntry();

	// QSettingsEntry interface
	QSettingsLoader *getLoader() const Q_DECL_OVERRIDE;
};

#endif // QSETTINGSLOADERENTRY_H
