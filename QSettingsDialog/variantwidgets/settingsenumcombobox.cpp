#include "settingsenumcombobox.h"

SettingsEnumComboBox::SettingsEnumComboBox(const QMetaEnum &metaEnum, QWidget *parent) :
	QSettingsWidget(parent),
	metaEnum(metaEnum)
{
	QStringList enumValues;
	for(int i = 0; i < this->metaEnum.keyCount(); i++)
		enumValues.append(QString::fromLocal8Bit(this->metaEnum.key(i)));
	this->addItems(enumValues);
}

void SettingsEnumComboBox::setValue(const QVariant &value)
{
	auto intVal = value.toInt();
	for(int i = 0; i < this->metaEnum.keyCount(); i++) {
		if(this->metaEnum.value(i) == intVal) {
			this->setCurrentIndex(i);
			break;
		}
	}
}

QVariant SettingsEnumComboBox::getValue() const
{
	return this->metaEnum.value(this->currentIndex());
}

void SettingsEnumComboBox::resetValue()
{
}
