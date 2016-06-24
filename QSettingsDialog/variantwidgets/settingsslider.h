#ifndef SETTINGSSLIDER_H
#define SETTINGSSLIDER_H

#include "qsettingswidget.h"
#include <QSlider>

class SettingsSlider : public QSettingsWidget<QSlider>
{
public:
	SettingsSlider(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSSLIDER_H
