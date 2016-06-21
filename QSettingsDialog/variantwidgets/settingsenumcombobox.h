#ifndef SETTINGSENUMCOMBOBOX_H
#define SETTINGSENUMCOMBOBOX_H

#include "qsettingswidget.h"
#include <QComboBox>
#include <QMetaEnum>

class SettingsEnumComboBox : public QSettingsWidget<QComboBox>
{
	Q_OBJECT
	Q_PROPERTY(bool translated READ translated WRITE setTranslated NOTIFY translatedChanged)

public:
	SettingsEnumComboBox(const QMetaEnum &metaEnum, QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

	bool translated() const;

public slots:
	void setTranslated(bool translated);

signals:
	void translatedChanged(bool translated);

private:
	QMetaEnum metaEnum;
	bool m_translated;
};

#endif // SETTINGSENUMCOMBOBOX_H
