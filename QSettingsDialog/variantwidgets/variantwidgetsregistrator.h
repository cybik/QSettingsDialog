#ifndef VARIANTWIDGETSREGISTRATOR_H
#define VARIANTWIDGETSREGISTRATOR_H

#include "qsettingsdialog_global.h"

class QSETTINGSDIALOGSHARED_EXPORT VariantWidgetsRegistrator
{
public:
	static void registerVariantWidgets();
	static void registerEnumFactories();
	static void registerExtendedVariantWidgets();
};

#endif // VARIANTWIDGETSREGISTRATOR_H
