#include "settingscheckbox.h"

SettingsCheckBox::SettingsCheckBox(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsCheckBox::setValue(const QVariant &value)
{
	this->setChecked(value.toBool());
}

QVariant SettingsCheckBox::getValue() const
{
	return this->isChecked();
}

void SettingsCheckBox::resetValue()
{
	this->setChecked(false);
}
