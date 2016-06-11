#include "delayedtestentry.h"
#include <QDebug>
#include <QTimer>
#include "swidget.h"

DelayedTestEntry::DelayedTestEntry(QVariant data, int delayMSecs, QObject *parent) :
	QAsyncSettingsLoader(parent),
	data(data),
	delayMSecs(delayMSecs)
{}

QString DelayedTestEntry::entryName() const
{
	return "Test Entry";
}

bool DelayedTestEntry::isOptional() const
{
	return false;
}

QString DelayedTestEntry::tooltip() const
{
	return "Baum == 42";
}

QSettingsWidgetBase *DelayedTestEntry::createWidget(QWidget *parent)
{
	return new TestWidget(parent, true);
}

QSettingsLoader *DelayedTestEntry::getLoader()
{
	return this;
}

void DelayedTestEntry::freeLoader(QSettingsLoader *loader)
{
}

void DelayedTestEntry::loadData()
{
	QTimer::singleShot(this->delayMSecs, this, [=]() {
		qDebug() << "LOADING" << this->data;
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
		qDebug() << "RESETTING to " << this->data;
		emit resetDone(true);
	});
}
