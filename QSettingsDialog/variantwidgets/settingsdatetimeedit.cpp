#include "settingsdatetimeedit.h"

SettingsDateEdit::SettingsDateEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setCalendarPopup(true);
}

void SettingsDateEdit::setValue(const QVariant &value)
{
	this->setDate(value.toDate());
}

QVariant SettingsDateEdit::getValue() const
{
	return this->date();
}

void SettingsDateEdit::resetValue()
{
	this->setDate(QDate());
}



SettingsTimeEdit::SettingsTimeEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsTimeEdit::setValue(const QVariant &value)
{
	qDebug("data");
	this->setTime(value.toTime());
}

QVariant SettingsTimeEdit::getValue() const
{
	return this->time();
}

void SettingsTimeEdit::resetValue()
{
	this->setTime(QTime());
}



SettingsDateTimeEdit::SettingsDateTimeEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setCalendarPopup(true);
}

void SettingsDateTimeEdit::setValue(const QVariant &value)
{
	this->setDateTime(value.toDateTime());
}

QVariant SettingsDateTimeEdit::getValue() const
{
	return this->dateTime();
}

void SettingsDateTimeEdit::resetValue()
{
	this->setDateTime(QDateTime());
}

