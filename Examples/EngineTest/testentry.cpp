#include "testentry.h"

TestEntry::TestEntry()
{

}

QVariant TestEntry::load(bool &userEdited)
{
	return QVariant();
}

bool TestEntry::save(const QVariant &data)
{
	return true;
}

bool TestEntry::reset()
{
	return true;
}

QString TestEntry::entryName() const
{
	return "Test Entry";
}

bool TestEntry::isOptional() const
{
	return true;
}

QSettingsWidgetBase *TestEntry::createWidget(QWidget *parent)
{
	return nullptr;
}
