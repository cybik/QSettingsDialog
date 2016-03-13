#ifndef SETTINGSDOUBLESPINBOX_H
#define SETTINGSDOUBLESPINBOX_H

#include "qsettingswidget.h"
#include "qsettingsvariantentry.h"
#include <QDoubleSpinBox>

class SettingsDoubleSpinBox : public QSettingsWidget<QDoubleSpinBox>
{
public:
	SettingsDoubleSpinBox(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	double state;
};

class DoubleSpinBoxFactory : public QSettingsWidgetFactory
{
public:
	DoubleSpinBoxFactory(double max = DBL_MAX, double min = DBL_MIN);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_OVERRIDE;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_OVERRIDE;

private:
	double min;
	double max;
};

#endif // SETTINGSDOUBLESPINBOX_H
