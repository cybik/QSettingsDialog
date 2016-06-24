#include "qsettingsdialog_global.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	//TODO register default dialog factory type here instead of in dialog
	VariantWidgetsRegistrator::registerVariantWidgets();
	VariantWidgetsRegistrator::registerEnumFactories();
	VariantWidgetsRegistrator::registerExtendedVariantWidgets();
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
