#include "settingscoloredit.h"

SettingsColorEdit::SettingsColorEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsColorEdit::setValue(const QVariant &value)
{
	this->setColor(value.value<QColor>());
}

QVariant SettingsColorEdit::getValue() const
{
	return this->color();
}

void SettingsColorEdit::resetValue()
{
	this->setColor(QColor());
}
