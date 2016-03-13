#ifndef SETTINGSCOLOREDIT_H
#define SETTINGSCOLOREDIT_H

#include "qsettingswidget.h"
#include <qcoloredit.h>

class SettingsColorEdit : public QSettingsWidget<QColorEdit>
{
public:
	SettingsColorEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	QColor state;
};

#endif // SETTINGSCOLOREDIT_H
