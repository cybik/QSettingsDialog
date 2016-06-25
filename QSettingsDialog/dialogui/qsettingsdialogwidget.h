#ifndef QSETTINGSDIALOGWIDGET_H
#define QSETTINGSDIALOGWIDGET_H

#include "qsettingsdialog_global.h"
#include "qsettingswidget.h"
#include <QWidget>
#include <QDialog>
#include <QIcon>
class QPushButton;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialogWidgetBase : public QSettingsWidget<QWidget>
{
public:
	QSettingsDialogWidgetBase(QWidget *parent = nullptr);

	virtual QString buttonText() const = 0;
	virtual QIcon buttonIcon() const;
	virtual void showDialog() = 0;

protected:
	void showEvent(QShowEvent *event) final;

private:
	QPushButton *btn;
};

template<typename TDialog>
class QSettingsDialogWidget : public QSettingsDialogWidgetBase
{
public:
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
