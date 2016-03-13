#include "settingsdatetimeedit.h"

SettingsDateEdit::SettingsDateEdit(QWidget *parent) :
	QSettingsWidget(parent),
	state()
{
	this->setCalendarPopup(true);
}

bool SettingsDateEdit::hasValueChanged() const
{
	return this->date() != this->state;
}

void SettingsDateEdit::resetValueChanged()
{
	this->state = this->date();
}

void SettingsDateEdit::setValue(const QVariant &value)
{
	this->setDate(value.toDate());
}

QVariant SettingsDateEdit::getValue()
{
	return this->date();
}

void SettingsDateEdit::resetValue()
{
	this->clear();
}



SettingsTimeEdit::SettingsTimeEdit(QWidget *parent) :
	QSettingsWidget(parent),
	state()
{}

bool SettingsTimeEdit::hasValueChanged() const
{
	return this->time() != this->state;
}

void SettingsTimeEdit::resetValueChanged()
{
	this->state = this->time();
}

void SettingsTimeEdit::setValue(const QVariant &value)
{
	this->setTime(value.toTime());
}

QVariant SettingsTimeEdit::getValue()
{
	return this->time();
}

void SettingsTimeEdit::resetValue()
{
	this->clear();
}



SettingsDateTimeEdit::SettingsDateTimeEdit(QWidget *parent) :
	QSettingsWidget(parent),
	state()
{
	this->setCalendarPopup(true);
}

bool SettingsDateTimeEdit::hasValueChanged() const
{
	return this->dateTime() != this->state;
}

void SettingsDateTimeEdit::resetValueChanged()
{
	this->state = this->dateTime();
}

void SettingsDateTimeEdit::setValue(const QVariant &value)
{
	this->setDateTime(value.toDateTime());
}

QVariant SettingsDateTimeEdit::getValue()
{
	return this->dateTime();
}

void SettingsDateTimeEdit::resetValue()
{
	this->clear();
}

