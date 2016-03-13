#include "settingscheckbox.h"

SettingsCheckBox::SettingsCheckBox(QWidget *parent) :
	QSettingsWidget(parent),
	resetState(false)
{}

bool SettingsCheckBox::hasValueChanged() const
{
	return this->isChecked() != this->resetState;
}

void SettingsCheckBox::resetValueChanged()
{
	this->resetState = this->isChecked();
}

void SettingsCheckBox::setValue(const QVariant &value)
{
	this->setChecked(value.toBool());
}

QVariant SettingsCheckBox::getValue()
{
	return this->isChecked();
}

void SettingsCheckBox::resetValue()
{
	this->setChecked(false);
}
