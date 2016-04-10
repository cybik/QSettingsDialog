#ifndef SETTINGSSPINBOX_H
#define SETTINGSSPINBOX_H

#include "qsettingswidget.h"
#include "qsettingsvariantentry.h"
#include <QSpinBox>

class SettingsSpinBox : public QSettingsWidget<QSpinBox>
{
public:
	SettingsSpinBox(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	int state;
};

class SettingsDoubleSpinBox : public QSettingsWidget<QDoubleSpinBox>
{
public:
	SettingsDoubleSpinBox(QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	double state;
};

class SpinBoxFactory : public QSettingsWidgetFactory
{
public:
	SpinBoxFactory(int max = INT_MAX, int min = INT_MIN);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_FINAL;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_FINAL;

private:
	int min;
	int max;
};

class DoubleSpinBoxFactory : public QSettingsWidgetFactory
{
public:
	DoubleSpinBoxFactory(double max = DBL_MAX, double min = DBL_MIN);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_FINAL;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_FINAL;

private:
	double min;
	double max;
};

#endif // SETTINGSSPINBOX_H
