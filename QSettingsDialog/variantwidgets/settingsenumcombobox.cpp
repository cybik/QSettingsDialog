#include "settingsenumcombobox.h"
#include <QCoreApplication>

SettingsEnumComboBox::SettingsEnumComboBox(const QMetaEnum &metaEnum, QWidget *parent) :
	QSettingsWidget(parent),
	metaEnum(metaEnum),
	m_translated(false)
{
	this->setTranslated(true);
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
	this->setCurrentIndex(-1);
}

bool SettingsEnumComboBox::translated() const
{
	return m_translated;
}

void SettingsEnumComboBox::setTranslated(bool translated)
{
	if (m_translated == translated)
		return;
	m_translated = translated;

	auto cIndex = this->currentIndex();
	QStringList enumValues;
	for(int i = 0; i < this->metaEnum.keyCount(); i++) {
		QString text;
		if(translated)
			text = QCoreApplication::translate(this->metaEnum.name(), this->metaEnum.key(i));
		else
			text = QString::fromLocal8Bit(this->metaEnum.key(i));
		enumValues.append(text);
	}
	this->clear();
	this->addItems(enumValues);
	this->setCurrentIndex(cIndex);

	emit translatedChanged(translated);
}
