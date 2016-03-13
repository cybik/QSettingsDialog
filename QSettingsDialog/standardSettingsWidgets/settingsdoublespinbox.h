#ifndef SETTINGSDOUBLESPINBOX_H
#define SETTINGSDOUBLESPINBOX_H

#include "qsettingswidget.h"
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

#endif // SETTINGSDOUBLESPINBOX_H
