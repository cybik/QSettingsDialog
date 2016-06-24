#include "settingsslider.h"

SettingsSlider::SettingsSlider(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setOrientation(Qt::Horizontal);
}

void SettingsSlider::setValue(const QVariant &value)
{
	this->QSlider::setValue(value.toInt());
}

QVariant SettingsSlider::getValue() const
{
	return this->value();
}

void SettingsSlider::resetValue()
{
	this->QSlider::setValue(0);
}
