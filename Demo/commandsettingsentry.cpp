#include "commandsettingsentry.h"
#include <QLineEdit>

CommandSettingsEntry::CommandSettingsEntry(QString name, bool optional) :
	name(name),
	optional(optional)
{}

QString CommandSettingsEntry::entryName() const
{
	return name;
}

bool CommandSettingsEntry::isOptional() const
{
	return optional;
}

QWidget *CommandSettingsEntry::createWidget(QWidget *parent)
{
	return new QLineEdit(parent);
}

QSettingsLoader *CommandSettingsEntry::createLoader()
{
	return Q_NULLPTR;
}

void CommandSettingsEntry::setValue(QWidget *widget, const QVariant &value)
{
	static_cast<QLineEdit*>(widget)->setText(value.toString());
}

QVariant CommandSettingsEntry::getValue(QWidget *widget)
{
	return static_cast<QLineEdit*>(widget)->text();
}

void CommandSettingsEntry::resetWidget(QWidget *widget)
{
	static_cast<QLineEdit*>(widget)->setText(QString());
}
