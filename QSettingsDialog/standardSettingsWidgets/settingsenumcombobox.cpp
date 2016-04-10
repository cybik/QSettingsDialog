#include "settingsenumcombobox.h"

SettingsEnumComboBox::SettingsEnumComboBox(int typeId, QMetaEnum metaEnum, QWidget *parent) :
	QSettingsWidget(parent),
	typeId(typeId),
	metaEnum(metaEnum),
	resetState(0)
{
	this->setEditable(false);
	for(int i = 0, max = this->metaEnum.keyCount(); i < max; ++i)
		this->addItem(this->metaEnum.key(i), this->metaEnum.value(i));
	this->setCurrentIndex(0);
}

bool SettingsEnumComboBox::hasValueChanged() const
{
	return this->currentIndex() != this->resetState;
}

void SettingsEnumComboBox::resetValueChanged()
{
	this->resetState = this->currentIndex();
}

void SettingsEnumComboBox::setValue(const QVariant &value)
{
	this->setCurrentText(value.toString());
}

QVariant SettingsEnumComboBox::getValue()
{
	QVariant variant(this->currentText());
	bool ok = variant.convert(this->typeId);
	Q_ASSERT_X2(ok, "A QVariant combobox must always be able to convert it's data!");
	return variant;
}

void SettingsEnumComboBox::resetValue()
{
	this->setCurrentIndex(0);
}



EnumSettingsWidgetFactory::EnumSettingsWidgetFactory() :
	QSettingsWidgetFactory(),
	currentMetaEnum()
{}

bool EnumSettingsWidgetFactory::prepareForEnum(int typeId)
{
	if(!QMetaType::typeFlags(typeId).testFlag(QMetaType::IsEnumeration))
		return false;
	const QMetaObject *metaObject = QMetaType::metaObjectForType(typeId);
	if(!metaObject)
		return false;
	QByteArray name(QMetaType::typeName(typeId));
	if(name.isEmpty())
		return false;
	const int index = metaObject->indexOfEnumerator(name.mid(name.lastIndexOf("::") + 2));
	if(index == -1)
		return false;
	this->currentTypeId = typeId;
	this->currentMetaEnum = metaObject->enumerator(index);
	return true;
}

QSettingsWidgetBase *EnumSettingsWidgetFactory::createWidget(QWidget *parent)
{
	return new SettingsEnumComboBox(this->currentTypeId, this->currentMetaEnum, parent);
}

void EnumSettingsWidgetFactory::destroyWidget(QSettingsWidgetBase *widget)
{
	widget->asWidget()->deleteLater();
}
