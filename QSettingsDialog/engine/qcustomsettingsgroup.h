#ifndef QCUSTOMSETTINGSGROUP_H
#define QCUSTOMSETTINGSGROUP_H

#include "qsettingsdialog_global.h"
#include <QWidget>

class QSETTINGSDIALOGSHARED_EXPORT QCustomSettingsGroup
{
public:
	virtual ~QCustomSettingsGroup();

	virtual QWidget *asWidget() = 0;

	virtual bool load() = 0;
	virtual bool save() = 0;
	virtual bool reset() = 0;
};

#endif // QCUSTOMSETTINGSGROUP_H
