#ifndef QSETTINGSSETTINGSLOADER_H
#define QSETTINGSSETTINGSLOADER_H

#include "qsettingsdialog_global.h"
#include "qsettingsloader.h"
#include <QSettings>
#include <QScopedPointer>

class QSettingsSettingsLoaderPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsSettingsLoader : public QSimpleSettingsLoader
{
public:
	QSettingsSettingsLoader(const QString &key);
	QSettingsSettingsLoader(QSettings *settings, const QString &key, bool ownSettings = false);
	~QSettingsSettingsLoader();

	// QSimpleSettingsLoader interface
	bool load(QVariant outParam data, bool outParam userEdited) override;
	bool save(const QVariant &data) override;
	bool reset() override;

	static QHash<QString, QSettingsSettingsLoader*> createLoaders(QSettings *settings,
																  const QString &rootKey = QString(),
																  bool recursive = false);

private:
	QScopedPointer<QSettingsSettingsLoaderPrivate> d_ptr;

	static QHash<QString, QSettingsSettingsLoader*> createLoadersImpl(QSettings *settings,
																	  const QString &rootKey,
																	  bool recursive);
};

#endif // QSETTINGSSETTINGSLOADER_H
