#include "settingskeyedit.h"

SettingsKeyEdit::SettingsKeyEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsKeyEdit::setValue(const QVariant &value)
{
	this->setKeySequence(value.value<QKeySequence>());
}

QVariant SettingsKeyEdit::getValue() const
{
	return this->keySequence();
}

void SettingsKeyEdit::resetValue()
{
	this->clear();
}
