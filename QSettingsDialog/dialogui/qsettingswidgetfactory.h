#ifndef QSETTINGSWIDGETFACTORY_H
#define QSETTINGSWIDGETFACTORY_H

#include "qsettingsdialog_global.h"
#include "qsettingswidget.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetFactory
{
public:
	inline virtual ~QSettingsWidgetFactory() {}

	virtual QSettingsWidgetBase *createWidget(QWidget *parent) = 0;
};

template <class TSettingsWidget>
class GenericSettingsWidgetFactory : public QSettingsWidgetFactory
{
public:
	QSettingsWidgetBase *createWidget(QWidget *parent) final {
		return new TSettingsWidget(parent);
	}
};

//TypeA: sofisticated type; TypeB: simple base type
#define REGISTER_TYPE_CONVERTERS(TypeA, TypeB) do {\
	QMetaType::registerConverter<TypeA, TypeB>([](TypeA aVal) -> TypeB {\
		return (TypeB)aVal;\
	});\
	QMetaType::registerConverter<TypeB, TypeA>([](TypeB bVal) -> TypeA {\
		return TypeA(bVal);\
	});\
} while(false)

#define REGISTER_FLAG_CONVERTERS(FlagsType) REGISTER_TYPE_CONVERTERS(FlagsType, int)

#endif // QSETTINGSWIDGETFACTORY_H
