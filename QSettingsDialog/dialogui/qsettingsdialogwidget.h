#ifndef QSETTINGSDIALOGWIDGET_H
#define QSETTINGSDIALOGWIDGET_H

#include "qsettingsdialog_global.h"
#include "qsettingswidget.h"
#include <QWidget>
#include <QDialog>
#include <QIcon>
class QPushButton;

//! The base class for dialog based edit widgets in the settings dialog @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialogWidgetBase : public QSettingsWidget<QWidget>
{
public:
	//! Creates a new dialog widget with a parent
	QSettingsDialogWidgetBase(QWidget *parent = nullptr);

	//! Returns the text to be shown in the dialog button
	virtual QString buttonText() const = 0;
	//! Returns the icon to be shown in the dialog button
	virtual QIcon buttonIcon() const;
	//! Will be called to show the dialog
	virtual void showDialog() = 0;

protected:
	//! Overwritten to load button data when showed
	void showEvent(QShowEvent *event) final;

private:
	QPushButton *btn;
};

//! A generic class to easily create a dialog widget from a normal one @ingroup grp_dialogui
template<typename TDialog>
class QSettingsDialogWidget : public QSettingsDialogWidgetBase //TODO dont require QDialog, allow any widget
{
public:
	//! Creates a new dialog widget with a parent
	QSettingsDialogWidget(QWidget *parent = nullptr) :
		QSettingsDialogWidgetBase(parent),
		dialog(new TDialog(this))
	{}

	// QSettingsWidgetBase interface
	bool hasValueChanged() const final {
		return this->dialog->hasValueChanged();
	}
	void resetValueChanged() final {
		this->dialog->resetValueChanged();
	}
	void setValue(const QVariant &value) final {
		this->dialog->setValue(value);
	}
	QVariant getValue() const final {
		return this->dialog->getValue();
	}
	void resetValue() final {
		this->dialog->resetValue();
	}
	bool searchExpression(const QRegularExpression &regex) final {
		return this->dialog->searchExpression(regex);
	}

	// QSettingsDialogWidgetBase interface
	QString buttonText() const override {
		return this->dialog->windowTitle();
	}
	QIcon buttonIcon() const override {
		return this->dialog->windowIcon();
	}
	void showDialog() final {
		this->dialog->open();
	}

private:
	TDialog *dialog;
};

#endif // QSETTINGSDIALOGWIDGET_H
