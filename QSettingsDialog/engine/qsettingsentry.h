#ifndef QSETTINGSENTRY_H
#define QSETTINGSENTRY_H

#include "qsettingsdialog_global.h"
#include <QVariant>
#include "qsettingsloader.h"
#include "qsettingswidget.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsEntry
{
public:
	inline virtual ~QSettingsEntry() {}

	virtual QString entryName() const = 0;
	virtual bool isOptional() const = 0;
	virtual QString tooltip() const = 0;

	virtual QSettingsWidgetBase *createWidget(QWidget *parent) = 0;
	virtual inline void destroyWidget(QSettingsWidgetBase *widget) {
		widget->asWidget()->deleteLater();
	}

	virtual QSettingsLoader *getLoader() = 0;
	virtual inline void freeLoader(QSettingsLoader *loader) {Q_UNUSED(loader);}
};

#endif // QSETTINGSENTRY_H
