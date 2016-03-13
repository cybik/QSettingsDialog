#ifndef SETTINGSFONTCOMBOBOX_H
#define SETTINGSFONTCOMBOBOX_H

#include "qsettingswidget.h"
#include <QFontComboBox>

class SettingsFontComboBox : public QSettingsWidget<QFontComboBox>
{
public:
	SettingsFontComboBox(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	QFont state;
};

#endif // SETTINGSFONTCOMBOBOX_H
