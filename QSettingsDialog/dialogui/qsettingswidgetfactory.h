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

#define REGISTER_FLAG_CONVERTERS(FlagsType) do {\
	QMetaType::registerConverter<FlagsType, int>([](FlagsType f) -> int {\
		return (int)f;\
	});\
	QMetaType::registerConverter<int, FlagsType>([](int f) -> FlagsType {\
		return (FlagsType)f;\
	});\
} while(false)

#endif // QSETTINGSWIDGETFACTORY_H
