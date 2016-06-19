#ifndef SETTINGSKEYEDIT_H
#define SETTINGSKEYEDIT_H

#include "qsettingswidget.h"
#include <QKeySequenceEdit>

class SettingsKeyEdit : public QSettingsWidget<QKeySequenceEdit>
{
public:
	SettingsKeyEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSKEYEDIT_H
