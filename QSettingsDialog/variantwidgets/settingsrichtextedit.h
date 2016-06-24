#ifndef SETTINGSRICHTEXTEDIT_H
#define SETTINGSRICHTEXTEDIT_H

#include "qsettingswidget.h"
#include <QTextEdit>

class SettingsRichTextEdit : public QSettingsWidget<QTextEdit>
{
public:
	SettingsRichTextEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSRICHTEXTEDIT_H
