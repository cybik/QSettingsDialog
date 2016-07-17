#ifndef VARIANTWIDGETSREGISTRATOR_H
#define VARIANTWIDGETSREGISTRATOR_H

#include "qsettingsdialog_global.h"

//! A static class to globally register different types of edit widgets @ingroup grp_variantwidgets
class QSETTINGSDIALOGSHARED_EXPORT VariantWidgetsRegistrator
{
public:
	//! Registeres the default group widgets
	static void registerGroupWidgets();
	//! Registeres the default edit widgets
	static void registerVariantWidgets();
	//! Registeres the enum and flag edit widget facotries
	static void registerEnumFactories();
	//! Registeres the extended edit widgets
	static void registerExtendedVariantWidgets();
};

#endif // VARIANTWIDGETSREGISTRATOR_H
