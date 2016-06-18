#ifndef QSETTINGSWIDGETDIALOGENGINE_H
#define QSETTINGSWIDGETDIALOGENGINE_H

#include "qsettingsdialog_global.h"
#include "qsettingsdisplayengine.h"

class QSettingsWidgetDialogEngine : public QSettingsDisplayEngine
{
public:
	QSettingsDisplayInstance *createInstance() override;
};

#endif // QSETTINGSWIDGETDIALOGENGINE_H
