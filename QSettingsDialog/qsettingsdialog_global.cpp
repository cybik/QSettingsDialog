#include "qsettingsdialog_global.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	VariantWidgetsRegistrator::registerVariantWidgets();
	//TODO register default dialog factory type here instead of in dialog
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
