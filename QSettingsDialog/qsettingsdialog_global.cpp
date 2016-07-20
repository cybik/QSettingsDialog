#include "qsettingsdialog_global.h"
#include "qasyncsettingscontainer_p.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

void qSettingsDialogSetup()
{
	qRegisterMetaType<QAsyncSettingsContainerPrivate::EntryInfo>();
	qRegisterMetaType<QSharedPointer<QSettingsEntry>>();
	qRegisterMetaType<QSettingsDialog*>();

	bool ok;
	auto loadMode = qEnvironmentVariableIntValue(VARIANT_WIDGETS_AUTOLOAD, &ok);
	if(!ok)
		loadMode = AUTOLOAD_GROUPS | AUTOLOAD_WIDGETS | AUTOLOAD_ENUMS | AUTOLOAD_EXTENDED;

	if(loadMode & AUTOLOAD_GROUPS)
		VariantWidgetsRegistrator::registerGroupWidgets();
	if(loadMode & AUTOLOAD_WIDGETS)
		VariantWidgetsRegistrator::registerVariantWidgets();
	if(loadMode & AUTOLOAD_ENUMS)
		VariantWidgetsRegistrator::registerEnumFactories();
	if(loadMode & AUTOLOAD_EXTENDED)
		VariantWidgetsRegistrator::registerExtendedVariantWidgets();
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
