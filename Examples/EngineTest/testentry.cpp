#include "testentry.h"
#include <QDebug>
#include "swidget.h"

TestEntry::TestEntry(bool optional, bool working, QVariant data) :
	QSettingsLoaderEntry(working ? 0 : -1),
	data(data)
{
	this->setEntryName("Test Entry");
	this->setOptional(optional);
	this->setTooltip("Baum == 42");
}

bool TestEntry::load(QVariant outParam data, bool outParam userEdited)
{
	userEdited = !this->data.isNull();
	data = this->data;
	return true;
}

bool TestEntry::save(const QVariant &data)
{
	qDebug() << "SAVING from" << this->data << "to" << data;
	return true;
}

bool TestEntry::reset()
{
	qDebug() << "RESETTING to" << this->data;
	return true;
}
