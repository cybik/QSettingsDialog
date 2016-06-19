#ifndef SETTINGSFONTCOMBOBOX_H
#define SETTINGSFONTCOMBOBOX_H

#include "qsettingswidget.h"
#include <QFontComboBox>

class SettingsFontComboBox : public QSettingsWidget<QFontComboBox>
{
public:
	SettingsFontComboBox(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSFONTCOMBOBOX_H
