#ifndef QSETTINGSGROUPWIDGETFACTORY_H
#define QSETTINGSGROUPWIDGETFACTORY_H

#include "qsettingsdialog_global.h"
#include "qsettingsgroupwidget.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroupWidgetFactory
{
public:
	inline virtual ~QSettingsGroupWidgetFactory() {}

	virtual QSettingsGroupWidgetBase *createGroupWidget(QWidget *parent) = 0;
};

template <class TSettingsGroupWidget>
class GenericSettingsGroupWidgetFactory : public QSettingsGroupWidgetFactory
{
public:
	QSettingsGroupWidgetBase *createGroupWidget(QWidget *parent) final {
		return new TSettingsGroupWidget(parent);
	}
};

#endif // QSETTINGSGROUPWIDGETFACTORY_H
