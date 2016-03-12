#ifndef SETTINGSLINEEDIT_H
#define SETTINGSLINEEDIT_H

#include "qsettingswidget.h"
#include <QLineEdit>

class SettingsLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	SettingsLineEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;
};

#endif // SETTINGSLINEEDIT_H
