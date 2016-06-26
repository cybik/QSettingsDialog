#include "delayedtestentry.h"
#include <QDebug>
#include <QTimer>
#include "swidget.h"

DelayedTestEntry::DelayedTestEntry(QVariant data, int delayMSecs) :
	QAsyncSettingsLoader(),
	QSettingsEntry(1, nullptr),
	data(data),
	delayMSecs(delayMSecs)
{
	this->setEntryName("Delayed Entry");
	this->setTooltip("Baum == 42");
}

QSettingsLoader *DelayedTestEntry::getLoader()
{
	return this;
}

void DelayedTestEntry::freeLoader(QSettingsLoader *)
{
}

void DelayedTestEntry::loadData()
{
	QTimer::singleShot(this->delayMSecs, this, [=]() {
		emit loadDone(true, this->data, !this->data.isNull());
	});
}

void DelayedTestEntry::saveData(const QVariant &data)
{
	QTimer::singleShot(this->delayMSecs, this, [=]() {
		qDebug() << "SAVING from" << this->data << "to" << data;
		emit saveDone(true);
	});
}

void DelayedTestEntry::resetData()
{
	QTimer::singleShot(this->delayMSecs, this, [=]() {
		qDebug() << "RESETTING to" << this->data;
		emit resetDone(true);
	});
}
