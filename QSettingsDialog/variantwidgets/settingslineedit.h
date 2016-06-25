#ifndef SETTINGSLINEEDIT_H
#define SETTINGSLINEEDIT_H

#include "qsettingswidget.h"
#include <QLineEdit>
#include <QUuid>
#include <QValidator>

class SettingsLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	SettingsLineEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const override;
	void resetValueChanged() override;
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

class SettingsByteLineEdit : public SettingsLineEdit
{
public:
	SettingsByteLineEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
};

class SettingsUrlLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	SettingsUrlLineEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
};

class QUrlValidator : public QValidator
{
public:
	QUrlValidator(QObject *parent = nullptr);

	// QValidator interface
	State validate(QString &text, int &) const override;
	void fixup(QString &text) const override;
};

class SettingsUuidEdit : public QSettingsWidget<QLineEdit>
{
public:
	SettingsUuidEdit(QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

private:
	void generateId();

	static QUuid toUuid(QString text);
};

#endif // SETTINGSLINEEDIT_H
