#ifndef SETTINGSFLAGSCHECKLIST_H
#define SETTINGSFLAGSCHECKLIST_H

#include "qsettingswidget.h"
#include <QMetaEnum>
#include <QButtonGroup>

class SettingsFlagsCheckList : public QSettingsWidget<QWidget>
{
	Q_OBJECT

public:
	SettingsFlagsCheckList(const QMetaEnum &metaEnum, QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

private slots:
	void updateFlags(int value);
	void reloadFlags();

private:
	QMetaEnum metaEnum;
	QButtonGroup *checkGroup;
	int currentFlags;
};

#endif // SETTINGSFLAGSCHECKLIST_H
