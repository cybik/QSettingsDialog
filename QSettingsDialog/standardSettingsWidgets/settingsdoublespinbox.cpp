#include "settingsdoublespinbox.h"

SettingsDoubleSpinBox::SettingsDoubleSpinBox(QWidget *parent) :
	QSettingsWidget(parent),
	state(0.0)
{
	this->setRange(DBL_MIN, DBL_MAX);
}

bool SettingsDoubleSpinBox::hasValueChanged() const
{
	return this->value() != this->state;
}

void SettingsDoubleSpinBox::resetValueChanged()
{
	this->state = this->value();
}

void SettingsDoubleSpinBox::setValue(const QVariant &value)
{
	this->QDoubleSpinBox::setValue(value.toDouble());
}

QVariant SettingsDoubleSpinBox::getValue()
{
	return this->value();
}

void SettingsDoubleSpinBox::resetValue()
{
	this->clear();
}
