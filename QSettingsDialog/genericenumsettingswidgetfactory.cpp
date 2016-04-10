#include "genericenumsettingswidgetfactory.h"
#include "standardSettingsWidgets/settingsenumcombobox.h"

GenericEnumSettingsWidgetFactory::GenericEnumSettingsWidgetFactory(bool asFlags, bool preferRadioList) :
	QSettingsWidgetFactory(),
	asFlags(asFlags),
	preferRadioList(preferRadioList)
{}

QSettingsWidgetBase *GenericEnumSettingsWidgetFactory::createWidget(QWidget *parent)
{
	int typeId = this->typeId();
	QMetaEnum metaEnum = this->metaEnum();
	Q_ASSERT_X2(metaEnum.isValid(), "Invalid enum-type!");
	if(this->asFlags) {
		Q_ASSERT_X2(metaEnum.isFlag(), "You have to use a flag-enum to show it as flags!");
		return Q_NULLPTR;
	} else {
		if(this->preferRadioList)
			return Q_NULLPTR;
		else
			return new SettingsEnumComboBox(typeId, metaEnum, parent);
	}
}

void GenericEnumSettingsWidgetFactory::destroyWidget(QSettingsWidgetBase *widget)
{
	widget->asWidget()->deleteLater();
}
