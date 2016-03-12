#include "settingslineedit.h"

SettingsLineEdit::SettingsLineEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

bool SettingsLineEdit::hasValueChanged() const
{
	return this->isModified();
}

void SettingsLineEdit::resetValueChanged()
{
	this->setModified(false);
}

void SettingsLineEdit::setValue(const QVariant &value)
{
	this->setText(value.toString());
}

QVariant SettingsLineEdit::getValue()
{
	return this->text();
}

void SettingsLineEdit::resetValue()
{
	this->clear();
}
