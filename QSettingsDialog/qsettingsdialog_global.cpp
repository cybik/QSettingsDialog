#include "qsettingsdialog_global.h"
#include "qasyncsettingscontainer_p.h"
#include <QCoreApplication>

#include "variantwidgetsregistrator.h"

#define AUTOLOAD_GROUPS 0x1000
#define AUTOLOAD_WIDGETS 0x0100
#define AUTOLOAD_ENUMS 0x0010
#define AUTOLOAD_EXTENDED 0x0001

void qSettingsDialogSetup()
{
	qRegisterMetaType<QAsyncSettingsContainerPrivate::EntryInfo>();
	qRegisterMetaType<QSharedPointer<QSettingsEntry>>();
	qRegisterMetaType<QSettingsDialog*>();

#if VARIANT_WIDGETS_AUTOLOAD & AUTOLOAD_GROUPS
	VariantWidgetsRegistrator::registerGroupWidgets();
#endif
#if VARIANT_WIDGETS_AUTOLOAD & AUTOLOAD_WIDGETS
	VariantWidgetsRegistrator::registerVariantWidgets();
#endif
#if VARIANT_WIDGETS_AUTOLOAD & AUTOLOAD_ENUMS
	VariantWidgetsRegistrator::registerEnumFactories();
#endif
#if VARIANT_WIDGETS_AUTOLOAD & AUTOLOAD_EXTENDED
	VariantWidgetsRegistrator::registerExtendedVariantWidgets();
#endif
}

Q_COREAPP_STARTUP_FUNCTION(qSettingsDialogSetup)
