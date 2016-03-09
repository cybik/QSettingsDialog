#include "qsettingsgroup.h"
#include <QGroupBox>
#include <QFormLayout>

QSettingsGroup::QSettingsGroup(QGroupBox *box) :
	box(box),
	widget(Q_NULLPTR),
	layout(new QFormLayout(this->box))
{
	this->box->setLayout(this->layout);
}

QSettingsGroup::QSettingsGroup(QWidget *widget) :
	box(Q_NULLPTR),
	widget(widget),
	layout(new QFormLayout(this->box))
{
	this->widget->setLayout(this->layout);
}

QSettingsGroup::~QSettingsGroup()
{

}

bool QSettingsGroup::isActivated() const
{
	if(this->box && this->box->isCheckable())
		return this->box->isChecked();
	else
		return true;
}

QString QSettingsGroup::name() const
{
	if(this->box)
		return this->box->title();
	else
		return QString();
}

bool QSettingsGroup::isOptional() const
{
	if(this->box)
		return this->box->isCheckable();
	else
		return false;
}

void QSettingsGroup::setName(const QString &name)
{
	if(this->box)
		this->box->setTitle(name);
}

void QSettingsGroup::setOptional(bool optional)
{
	if(this->box) {
		this->box->setCheckable(optional);
		this->box->setChecked(!optional);
	}
}
