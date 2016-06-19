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

#endif // QSETTINGSWIDGETFACTORY_H
