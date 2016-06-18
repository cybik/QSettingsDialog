#include "qsettingswidgetdialogengine.h"
#include "settingsdisplaydialog.h"

QSettingsDisplayInstance *QSettingsWidgetDialogEngine::createInstance()
{
	return new SettingsDisplayDialog(nullptr);
}
