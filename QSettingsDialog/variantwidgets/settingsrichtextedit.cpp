#include "settingsrichtextedit.h"

SettingsRichTextEdit::SettingsRichTextEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsRichTextEdit::setValue(const QVariant &value)
{
	this->setHtml(value.toString());
}

QVariant SettingsRichTextEdit::getValue() const
{
	return this->toHtml();
}

void SettingsRichTextEdit::resetValue()
{
	this->clear();
}
