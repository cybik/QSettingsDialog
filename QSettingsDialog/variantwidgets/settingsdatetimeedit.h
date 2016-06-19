#ifndef SETTINGSDATEEDIT_H
#define SETTINGSDATEEDIT_H

#include "qsettingswidget.h"
#include <QDateTimeEdit>

class SettingsDateEdit : public QSettingsWidget<QDateEdit>
{
public:
	SettingsDateEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

class SettingsTimeEdit : public QSettingsWidget<QTimeEdit>
{
public:
	SettingsTimeEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

class SettingsDateTimeEdit : public QSettingsWidget<QDateTimeEdit>
{
public:
	SettingsDateTimeEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

#endif // SETTINGSDATEEDIT_H
