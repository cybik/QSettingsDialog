#include "settingsfontcombobox.h"

SettingsFontComboBox::SettingsFontComboBox(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsFontComboBox::setValue(const QVariant &value)
{
	this->setCurrentFont(value.value<QFont>());
}

QVariant SettingsFontComboBox::getValue() const
{
	return this->currentFont();
}

void SettingsFontComboBox::resetValue()
{
	this->setCurrentIndex(-1);
}
