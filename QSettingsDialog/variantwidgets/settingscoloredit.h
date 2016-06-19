#ifndef SETTINGSCOLOREDIT_H
#define SETTINGSCOLOREDIT_H

#include "qsettingswidget.h"
#include <qcoloredit.h>

class SettingsColorEdit : public QSettingsWidget<QColorEdit>
{
public:
	SettingsColorEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSCOLOREDIT_H
