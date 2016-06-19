#ifndef SETTINGSENUMCOMBOBOX_H
#define SETTINGSENUMCOMBOBOX_H

#include "qsettingswidget.h"
#include <QComboBox>
#include <QMetaEnum>

class SettingsEnumComboBox : public QSettingsWidget<QComboBox>
{
public:
	SettingsEnumComboBox(const QMetaEnum &metaEnum, QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

private:
	QMetaEnum metaEnum;
};

#endif // SETTINGSENUMCOMBOBOX_H
