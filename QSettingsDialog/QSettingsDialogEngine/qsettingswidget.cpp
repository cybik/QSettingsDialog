#include "qsettingswidget.h"

QSettingsWidgetBase::QSettingsWidgetBase() :
	changedCache()
{}

QSettingsWidgetBase::~QSettingsWidgetBase() {}

bool QSettingsWidgetBase::hasValueChanged() const
{
	return (this->changedCache != this->getValue());
}

void QSettingsWidgetBase::resetValueChanged()
{
	this->changedCache = this->getValue();
}
