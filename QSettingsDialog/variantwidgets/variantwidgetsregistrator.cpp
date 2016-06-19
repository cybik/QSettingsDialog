#include "variantwidgetsregistrator.h"
#include "qsettingswidgetdialogengine.h"
#include <limits>

#include "settingscheckbox.h"
#include "settingsspinbox.h"
#include "settingslineedit.h"
#include "settingsdatetimeedit.h"
#include "settingscoloredit.h"
#include "settingslistedit.h"
#include "settingsfontcombobox.h"
#include "settingskeyedit.h"

void VariantWidgetsRegistrator::registerVariantWidgets()
{
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsCheckBox>(QMetaType::Bool);
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Int,
													   new SpinBoxFactory(std::numeric_limits<int>::max(),
																		  std::numeric_limits<int>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::UInt,
													   new SpinBoxFactory(std::numeric_limits<int>::max(), 0));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Double,
													   new DoubleSpinBoxFactory(std::numeric_limits<double>::max(),
																				std::numeric_limits<double>::min()));
	//TODO QChar
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsLineEdit>(QMetaType::QString);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsByteLineEdit>(QMetaType::QByteArray);
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Long,
													   new SpinBoxFactory(std::numeric_limits<int>::max(),
																		  std::numeric_limits<int>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::LongLong,
													   new SpinBoxFactory(std::numeric_limits<int>::max(),
																		  std::numeric_limits<int>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Short,
													   new SpinBoxFactory(std::numeric_limits<short>::max(),
																		  std::numeric_limits<short>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Char,
													   new SpinBoxFactory(std::numeric_limits<char>::max(),
																		  std::numeric_limits<char>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::ULong, new SpinBoxFactory(std::numeric_limits<int>::max(), 0));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::ULongLong, new SpinBoxFactory(std::numeric_limits<int>::max(), 0));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::UShort, new SpinBoxFactory(std::numeric_limits<unsigned short>::max(), 0));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::SChar,
													   new SpinBoxFactory(std::numeric_limits<signed char>::max(),
																		  std::numeric_limits<signed char>::min()));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::UChar, new SpinBoxFactory(std::numeric_limits<unsigned char>::max(), 0));
	QSettingsWidgetDialogEngine::registerGlobalFactory(QMetaType::Float,
													   new DoubleSpinBoxFactory(std::numeric_limits<float>::max(),
																				std::numeric_limits<float>::min()));
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsDateEdit>(QMetaType::QDate);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsTimeEdit>(QMetaType::QTime);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsColorEdit>(QMetaType::QColor);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsListEditWidget>(QMetaType::QStringList);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsUrlLineEdit>(QMetaType::QUrl);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsDateTimeEdit>(QMetaType::QDateTime);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsFontComboBox>(QMetaType::QFont);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsKeyEdit>(QMetaType::QKeySequence);
	QSettingsWidgetDialogEngine::registerGlobalWidgetType<SettingsUuidEdit>(QMetaType::QUuid);
	//TODO ENUMS!!!

	//TODO planned: QPathEdit, QIconEdit(?), QLocale, uuid generator, timeedit, date->now
}
