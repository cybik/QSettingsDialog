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
	qDebug() << value;
	this->setCurrentText(value.toString());
}

QVariant SettingsEnumComboBox::getValue()
{
	if(this->metaEnum.isFlag()) {
		QVariant variant(this->currentData());
		bool ok = variant.convert(this->typeId);
		Q_ASSERT_X2(ok, "Failed to convert QMetaEnum-Flag to QVariant");
		return variant;
	} else {
		QVariant variant(this->currentText());
		bool ok = variant.convert(this->typeId);
		Q_ASSERT_X2(ok, "Failed to convert QMetaEnum to QVariant");
		return variant;
	}
}

void SettingsEnumComboBox::resetValue()
{
	this->setCurrentIndex(0);
}



MetaEnumSettingsWidgetFactory::MetaEnumSettingsWidgetFactory() :
	QSettingsWidgetFactory(),
	currentMetaEnum()
{}

bool MetaEnumSettingsWidgetFactory::prepareForEnum(int typeId)
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

QSettingsWidgetBase *MetaEnumSettingsWidgetFactory::createWidget(QWidget *parent)
{
	return new SettingsEnumComboBox(this->currentTypeId, this->currentMetaEnum, parent);
}

void MetaEnumSettingsWidgetFactory::destroyWidget(QSettingsWidgetBase *widget)
{
	widget->asWidget()->deleteLater();
}
