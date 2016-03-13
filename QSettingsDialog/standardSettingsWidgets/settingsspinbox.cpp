#include "settingsspinbox.h"

SettingsSpinBox::SettingsSpinBox(QWidget *parent) :
	QSettingsWidget(parent),
	state(0)
{}

bool SettingsSpinBox::hasValueChanged() const
{
	return this->value() != this->state;
}

void SettingsSpinBox::resetValueChanged()
{
	this->state = this->value();
}

void SettingsSpinBox::setValue(const QVariant &value)
{
	this->QSpinBox::setValue(value.toInt());
}

QVariant SettingsSpinBox::getValue()
{
	return this->value();
}

void SettingsSpinBox::resetValue()
{
	this->clear();
}



SpinBoxFactory::SpinBoxFactory(int max, int min) :
	max(max),
	min(min)
{}

QSettingsWidgetBase *SpinBoxFactory::createWidget(QWidget *parent)
{
	SettingsSpinBox *box = new SettingsSpinBox(parent);
	box->setRange(this->min, this->max);
	return box;
}

void SpinBoxFactory::destroyWidget(QSettingsWidgetBase *widget)
{
	widget->asWidget()->deleteLater();
}
