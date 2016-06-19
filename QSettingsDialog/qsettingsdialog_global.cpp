#include "qsettingsdialog_global.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	VariantWidgetsRegistrator::registerVariantWidgets();
	//TODO register default dialog factory type
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
