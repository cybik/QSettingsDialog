#ifndef SETTINGSDATEEDIT_H
#define SETTINGSDATEEDIT_H

#include "qsettingswidget.h"
#include <QDateTimeEdit>

class SettingsDateEdit : public QSettingsWidget<QDateEdit>
{
public:
	SettingsDateEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	QDate state;
};

class SettingsTimeEdit : public QSettingsWidget<QTimeEdit>
{
public:
	SettingsTimeEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	QTime state;
};

class SettingsDateTimeEdit : public QSettingsWidget<QDateTimeEdit>
{
public:
	SettingsDateTimeEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	QDateTime state;
};

#endif // SETTINGSDATEEDIT_H
