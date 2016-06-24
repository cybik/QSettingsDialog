#ifndef SETTINGSPATHEDIT_H
#define SETTINGSPATHEDIT_H

#include "qsettingswidget.h"
#include <qpathedit.h>

class SettingsPathEdit : public QSettingsWidget<QPathEdit>
{
public:
	SettingsPathEdit(QWidget *parent = nullptr);

	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSPATHEDIT_H
