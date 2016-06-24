#include "settingspathedit.h"

SettingsPathEdit::SettingsPathEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setEditable(true);
}

void SettingsPathEdit::setValue(const QVariant &value)
{
	this->setPath(value.toString(), true);
}

QVariant SettingsPathEdit::getValue() const
{
	return this->path();
}

void SettingsPathEdit::resetValue()
{
	this->clear();
}
