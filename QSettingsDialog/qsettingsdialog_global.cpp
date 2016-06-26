#include "qsettingsdialog_global.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	VariantWidgetsRegistrator::registerVariantWidgets();
	VariantWidgetsRegistrator::registerEnumFactories();
	VariantWidgetsRegistrator::registerExtendedVariantWidgets();
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
