#include "testentry.h"
#include <QDebug>
#include "swidget.h"

TestEntry::TestEntry(bool optional, bool working, QVariant data, bool hasName) :
	optional(optional),
	working(working),
	data(data),
	hasName(hasName)
{}

QVariant TestEntry::load(bool &userEdited)
{
	qDebug() << "LOADING" << this->data;
	userEdited = !this->data.isNull();
	return this->data;
}

bool TestEntry::save(const QVariant &data)
{
	qDebug() << "SAVING from" << this->data << "to" << data;
	return true;
}

bool TestEntry::reset()
{
	qDebug() << "RESETTING to " << this->data;
	return true;
}

QString TestEntry::entryName() const
{
	return this->hasName ? "Test Entry" : QString();
}

bool TestEntry::isOptional() const
{
	return this->optional;
}

QString TestEntry::tooltip() const
{
	return "Baum == 42";
}

QSettingsWidgetBase *TestEntry::createWidget(QWidget *parent)
{
	return this->working ? new TestWidget(parent, this->optional) : nullptr;
}
