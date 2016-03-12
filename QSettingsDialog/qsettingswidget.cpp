#include "qsettingswidget.h"
#include <QCheckBox>
#include "qsettingsgroup.h"

QSettingsWidgetBase::QSettingsWidgetBase() :
	optBox(Q_NULLPTR),
	group(Q_NULLPTR),
	origState(false)
{}

void QSettingsWidgetBase::setup(QSettingsGroup *group, QCheckBox *box)
{
	this->group = group;
	this->optBox = box;
}

bool QSettingsWidgetBase::hasChanges() const
{
	if(this->isActive() != this->origState)
		return true;
	else if(this->isActive())
		return this->hasValueChanged();
	else
		return false;
}

bool QSettingsWidgetBase::isActive() const
{
	return this->group->isActivated() &&
			(this->optBox ? this->optBox->isChecked() : true);
}

void QSettingsWidgetBase::setLoadState(bool checked)
{
	if(this->optBox)
		this->optBox->setChecked(checked);
	if(checked)
		this->group->setActive(true);
	this->resetValueChanged();
}

void QSettingsWidgetBase::resetChanged()
{
	this->origState = this->isActive();
	if(this->origState)
		this->resetValueChanged();
}
