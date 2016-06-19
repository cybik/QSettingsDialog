#ifndef SETTINGSCHECKBOX_H
#define SETTINGSCHECKBOX_H

#include "qsettingswidget.h"
#include <QCheckBox>

class SettingsCheckBox : public QSettingsWidget<QCheckBox>
{
public:
	SettingsCheckBox(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSCHECKBOX_H
