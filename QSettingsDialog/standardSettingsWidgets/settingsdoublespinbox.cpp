#include "settingsdoublespinbox.h"

SettingsDoubleSpinBox::SettingsDoubleSpinBox(QWidget *parent) :
	QSettingsWidget(parent),
	state(0.0)
{}

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



DoubleSpinBoxFactory::DoubleSpinBoxFactory(double max, double min) :
	max(max),
	min(min)
{}

QSettingsWidgetBase *DoubleSpinBoxFactory::createWidget(QWidget *parent)
{
	SettingsDoubleSpinBox *box = new SettingsDoubleSpinBox(parent);
	box->setRange(this->min, this->max);
	return box;
}

void DoubleSpinBoxFactory::destroyWidget(QSettingsWidgetBase *widget)
{
	widget->asWidget()->deleteLater();
}

