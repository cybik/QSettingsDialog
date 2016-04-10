#ifndef SETTINGSENUMCOMBOBOX_H
#define SETTINGSENUMCOMBOBOX_H

#include "qsettingswidget.h"
#include "qsettingsvariantentry.h"
#include <QComboBox>
#include <QMetaEnum>

class SettingsEnumComboBox : public QSettingsWidget<QComboBox>
{
public:
	SettingsEnumComboBox(int typeId, QMetaEnum metaEnum, QWidget *parent = Q_NULLPTR);

	// QSettingsWidgetBase interface
	bool hasValueChanged() const Q_DECL_OVERRIDE;
	void resetValueChanged() Q_DECL_OVERRIDE;
	void setValue(const QVariant &value) Q_DECL_OVERRIDE;
	QVariant getValue() Q_DECL_OVERRIDE;
	void resetValue() Q_DECL_OVERRIDE;

private:
	int typeId;
	QMetaEnum metaEnum;
	int resetState;
};

class MetaEnumSettingsWidgetFactory : public QSettingsWidgetFactory
{
public:
	MetaEnumSettingsWidgetFactory();

	bool prepareForEnum(int typeId);

	// QSettingsWidgetFactory interface
	QSettingsWidgetBase *createWidget(QWidget *parent) Q_DECL_FINAL;
	void destroyWidget(QSettingsWidgetBase *widget) Q_DECL_FINAL;

private:
	int currentTypeId;
	QMetaEnum currentMetaEnum;
};

#endif // SETTINGSENUMCOMBOBOX_H
