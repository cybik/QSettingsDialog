#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include <QScopedPointer>
#include "qsettingsloader.h"

class QSettingsEntryPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsEntry
{
public:
	QSettingsEntry(int metatype, QSettingsLoader *loader);
	virtual ~QSettingsEntry();

	QString entryName() const;
	void setEntryName(const QString &name);
	bool isOptional() const;
	void setOptional(bool optional);
	QString tooltip() const;
	void setTooltip(const QString &tooltip);

	virtual int metatype() const;
	virtual QSettingsLoader *getLoader();
	virtual void freeLoader(QSettingsLoader *loader);

private:
	QScopedPointer<QSettingsEntryPrivate> d_ptr;
};

#endif // QSETTINGSENTRY_H
