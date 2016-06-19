#include "settingsenumwidgetfactory.h"
#include <QComboBox>
#include <QDebug>

class SettingsEnumComboBox : public QSettingsWidget<QComboBox>
{
public:
	SettingsEnumComboBox(const QMetaEnum &metaEnum, QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

private:
	QMetaEnum metaEnum;
};



QSettingsWidgetBase *SettingsEnumWidgetFactory::createWidget(const QMetaEnum &metaEnum, QWidget *parent)
{
	return new SettingsEnumComboBox(metaEnum, parent);
}



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
	qDebug() << value
			 << value.toString()
			 << value.toInt();
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
