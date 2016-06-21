#ifndef SETTINGSFLAGSCHECKLIST_H
#define SETTINGSFLAGSCHECKLIST_H

#include "qsettingswidget.h"
#include <QMetaEnum>
#include <QButtonGroup>

class SettingsFlagsCheckList : public QSettingsWidget<QWidget>
{
	Q_OBJECT
	Q_PROPERTY(bool translated READ translated WRITE setTranslated NOTIFY translatedChanged)

public:
	SettingsFlagsCheckList(const QMetaEnum &metaEnum, QWidget *parent = nullptr);

	// QSettingsWidgetBase interface
	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;

	bool translated() const;

public slots:
	void setTranslated(bool translated);

signals:
	void translatedChanged(bool translated);

private slots:
	void updateFlags(int value);
	void reloadFlags();

private:
	QMetaEnum metaEnum;
	QButtonGroup *checkGroup;
	int currentFlags;
	bool m_translated;
};

#endif // SETTINGSFLAGSCHECKLIST_H
