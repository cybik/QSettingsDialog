#ifndef SETTINGSRICHTEXTEDIT_H
#define SETTINGSRICHTEXTEDIT_H

#include "qsettingswidget.h"
#include <QTextEdit>
#include <QFontComboBox>
#include <QDoubleSpinBox>

class SettingsRichTextEdit : public QSettingsWidget<QTextEdit>
{
	Q_OBJECT

public:
	SettingsRichTextEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

protected:
	void contextMenuEvent(QContextMenuEvent *e) override;

private slots:
	void updateActionsStatus();
	void editFont();
	void editColor();

private:
	QAction *boldAction;
	QAction *italicAction;
	QAction *underlinedAction;
};

#endif // SETTINGSRICHTEXTEDIT_H
