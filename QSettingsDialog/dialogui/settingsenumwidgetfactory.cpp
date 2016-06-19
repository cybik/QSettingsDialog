#include "settingsenumwidgetfactory.h"

#include "settingsenumcombobox.h"
#include "settingsflagschecklist.h"

QSettingsWidgetBase *SettingsEnumWidgetFactory::createWidget(const QMetaEnum &metaEnum, QWidget *parent)
{
	if(metaEnum.isFlag())
		return new SettingsFlagsCheckList(metaEnum, parent);
	else
		return new SettingsEnumComboBox(metaEnum, parent);
}



