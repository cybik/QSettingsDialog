#include "settingsflagschecklist.h"
#include <QVBoxLayout>
#include <QCheckBox>

SettingsFlagsCheckList::SettingsFlagsCheckList(const QMetaEnum &metaEnum, QWidget *parent) :
	QSettingsWidget(parent),
	metaEnum(metaEnum),
	checkGroup(new QButtonGroup(this)),
	currentFlags(0)
{
	this->checkGroup->setExclusive(false);
	connect(this->checkGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
			this, &SettingsFlagsCheckList::updateFlags);

	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(QMargins());
	this->setLayout(layout);

	for(int i = 0; i < this->metaEnum.keyCount(); i++) {
		auto box = new QCheckBox(QString::fromLocal8Bit(this->metaEnum.key(i)), this);
		layout->addWidget(box);
		this->checkGroup->addButton(box, this->metaEnum.value(i));
	}
}

void SettingsFlagsCheckList::setValue(const QVariant &value)
{
	this->currentFlags = value.toInt();
	this->reloadFlags();
}

QVariant SettingsFlagsCheckList::getValue() const
{
	return this->currentFlags;
}

void SettingsFlagsCheckList::resetValue()
{
	this->currentFlags = 0;
	this->reloadFlags();
}

void SettingsFlagsCheckList::updateFlags(int value)
{
	if(this->checkGroup->button(value)->isChecked())
		this->currentFlags |= value;
	else
		this->currentFlags &= ~value;
	this->reloadFlags();
}

void SettingsFlagsCheckList::reloadFlags()
{
	for(int i = 0; i < this->metaEnum.keyCount(); i++) {
		auto value = this->metaEnum.value(i);
		this->checkGroup->button(value)->setChecked((this->currentFlags & value) == value);
	}
}
