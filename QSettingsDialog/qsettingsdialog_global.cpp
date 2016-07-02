#include "qsettingsdialog_global.h"
#include "qasyncsettingscontainer_p.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	qRegisterMetaType<QAsyncSettingsContainerPrivate::EntryInfo>();
	qRegisterMetaType<QSharedPointer<QSettingsEntry>>();
	qRegisterMetaType<QSettingsDialog*>();

	VariantWidgetsRegistrator::registerVariantWidgets();
	VariantWidgetsRegistrator::registerEnumFactories();
	VariantWidgetsRegistrator::registerExtendedVariantWidgets();
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
