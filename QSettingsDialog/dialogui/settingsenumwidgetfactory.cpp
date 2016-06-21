#include "settingsenumwidgetfactory.h"
#include <QMetaObject>

#include "settingsenumcombobox.h"
#include "settingsflagschecklist.h"

SettingsEnumWidgetFactory::SettingsEnumWidgetFactory(const QMetaEnum &metaEnum) :
	metaEnum(metaEnum)
{}

QSettingsWidgetBase *SettingsEnumWidgetFactory::createWidget(QWidget *parent)
{
	if(this->metaEnum.isFlag())
		return new SettingsFlagsCheckList(this->metaEnum, parent);
	else
		return new SettingsEnumComboBox(this->metaEnum, parent);
}



int SettingsEnumWidgetRegistry::priority() const
{
	return 42;
}

QSharedPointer<QSettingsWidgetFactory> SettingsEnumWidgetRegistry::tryResolve(int displayId)
{
	auto metaObject = QMetaType::metaObjectForType(displayId);
	if(metaObject) {
		QStringList metaNameList = QString::fromLocal8Bit(QMetaType::typeName(displayId)).split(QStringLiteral("::"));
		int index = -1;
		QString testName = metaNameList.takeLast();
		forever {
			index = metaObject->indexOfEnumerator(testName.toLocal8Bit().constData());
			if(index >= 0)
				break;
			else if(metaNameList.isEmpty())
				break;
			else
				testName = testName.prepend(metaNameList.takeLast() + QStringLiteral("::"));
		}

		auto metaEnum = metaObject->enumerator(index);
		if(metaEnum.isValid())
			return QSharedPointer<SettingsEnumWidgetFactory>(new SettingsEnumWidgetFactory(metaEnum));
	}

	return QSharedPointer<SettingsEnumWidgetFactory>();
}
