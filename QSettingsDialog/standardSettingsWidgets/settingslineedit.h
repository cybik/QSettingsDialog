#ifndef SETTINGSLINEEDIT_H
#define SETTINGSLINEEDIT_H

#include "qsettingswidget.h"
#include <QLineEdit>
#include <QValidator>

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

class SettingsUrlLineEdit : public QSettingsWidget<QLineEdit>
{
public:
	SettingsUrlLineEdit(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;
};

class QUrlValidator : public QValidator
{
public:
	QUrlValidator(QObject *parent = Q_NULLPTR);

	// QValidator interface
	State validate(QString &text, int &) const Q_DECL_OVERRIDE;
	void fixup(QString &text) const Q_DECL_OVERRIDE;
};

#endif // SETTINGSLINEEDIT_H
