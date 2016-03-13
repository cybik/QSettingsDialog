#include "settingsfontcombobox.h"

SettingsFontComboBox::SettingsFontComboBox(QWidget *parent) :
	QSettingsWidget(parent),
	state()
{}

bool SettingsFontComboBox::hasValueChanged() const
{
	return this->currentFont() != this->state;
}

void SettingsFontComboBox::resetValueChanged()
{
	this->state = this->currentFont();
}

void SettingsFontComboBox::setValue(const QVariant &value)
{
	this->setCurrentFont(value.value<QFont>());
}

QVariant SettingsFontComboBox::getValue()
{
	return this->currentFont();
}

void SettingsFontComboBox::resetValue()
{
	this->setCurrentIndex(-1);
}
