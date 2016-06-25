#ifndef QSETTINGSWIDGET_H
#define QSETTINGSWIDGET_H

#include "qsettingsdialog_global.h"
#include <QWidget>
#include <QVariant>
#include <QRegularExpression>
#include "qsettingsentry.h"

class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetBase
{
public:
	QSettingsWidgetBase();
	virtual ~QSettingsWidgetBase();

	virtual QWidget *asWidget() = 0;
	virtual void initialize(const QSettingsEntry::UiPropertyMap &uiPropertyMap) = 0;

	virtual bool hasValueChanged() const;
	virtual void resetValueChanged();

	virtual void setValue(const QVariant &value) = 0;
	virtual QVariant getValue() const = 0;
	virtual void resetValue() = 0;

	virtual inline bool searchExpression(const QRegularExpression &regex) {
		return regex.pattern().isEmpty();
	}

private:
	QVariant changedCache;
};

template <class Widget>
class QSettingsWidget : public Widget, public QSettingsWidgetBase
{
public:
	inline QSettingsWidget(QWidget *parent = nullptr) :
		Widget(parent),
		QSettingsWidgetBase()
	{}

	inline QWidget *asWidget() final {
		return this;
	}
	void initialize(const QSettingsEntry::UiPropertyMap &uiPropertyMap) override {
		for(QSettingsEntry::UiPropertyMap::const_iterator it = uiPropertyMap.constBegin(), end = uiPropertyMap.constEnd(); it != end; ++it)
			this->setProperty(it.key().toLocal8Bit().constData(), it.value());
	}
};

Q_DECLARE_METATYPE(QSettingsWidgetBase*)

#endif // QSETTINGSWIDGET_H
