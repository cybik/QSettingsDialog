#ifndef QSETTINGSWIDGET_H
#define QSETTINGSWIDGET_H

#include "qsettingsdialog_global.h"
class QCheckBox;
class QSettingsGroup;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetBase
{
	friend class QSettingsDialog;
	friend class QSettingsDialogPrivate;
	friend class QSettingsGroup;

public:	
	QSettingsWidgetBase();
	virtual inline ~QSettingsWidgetBase() {}

	virtual QWidget *asWidget() = 0;

	virtual bool hasValueChanged() const = 0;
	virtual void resetValueChanged() = 0;

	virtual void setValue(const QVariant &value) = 0;
	virtual QVariant getValue() = 0;
	virtual void resetValue() = 0;

private:
	//internal use only
	QCheckBox *optBox;
	QSettingsGroup *group;
	bool origState;

	void setup(QSettingsGroup *group, QCheckBox *optBox);
	bool hasChanges() const;
	bool isActive() const;
	void setLoadState(bool checked);
	void resetChanged();
};

template <class Widget>
class QSettingsWidget : public Widget, public QSettingsWidgetBase
{
public:
	inline QSettingsWidget(QWidget *parent = Q_NULLPTR) :
		Widget(parent),
		QSettingsWidgetBase()
	{}

	inline QWidget *asWidget() Q_DECL_FINAL {
		return this;
	}
};

#endif // QSETTINGSWIDGET_H
