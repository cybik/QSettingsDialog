#ifndef SETTINGSCHECKBOX_H
#define SETTINGSCHECKBOX_H

#include "qsettingswidget.h"
#include <QCheckBox>

class SettingsCheckBox : public QSettingsWidget<QCheckBox>
{
public:
	SettingsCheckBox(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	bool resetState;
};

#endif // SETTINGSCHECKBOX_H
