#include "settingscoloredit.h"

SettingsColorEdit::SettingsColorEdit(QWidget *parent) :
	QSettingsWidget(parent),
	state()
{}

bool SettingsColorEdit::hasValueChanged() const
{
	return this->color() != this->state;
}

void SettingsColorEdit::resetValueChanged()
{
	this->state = this->color();
}

void SettingsColorEdit::setValue(const QVariant &value)
{
	this->setColor(value.value<QColor>());
}

QVariant SettingsColorEdit::getValue()
{
	return this->color();
}

void SettingsColorEdit::resetValue()
{
	this->setColor(QColor());
}
