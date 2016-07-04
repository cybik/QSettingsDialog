#ifndef QSETTINGSGROUPWIDGET_H
#define QSETTINGSGROUPWIDGET_H

#include "qsettingsdialog_global.h"
#include "qsettingsentry.h"
#include <QHash>
class QSettingsWidgetBase;
class QCheckBox;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroupWidgetBase
{
public:
	virtual ~QSettingsGroupWidgetBase();

	virtual QWidget *asWidget() = 0;
	virtual void initialize(const QSettingsEntry::UiPropertyMap &uiPropertyMap) = 0;

	virtual void setName(const QString &name) = 0;
	virtual void setTooltip(const QString &tooltip) = 0;
	virtual void setOptional(bool optional) = 0;

	virtual bool isChecked() const = 0;
	virtual void setChecked(bool checked) = 0;

	virtual void addWidgetRaw(QSharedPointer<QSettingsEntry> entry, QWidget *content, bool hasError);
	virtual void setEntryChecked(QSharedPointer<QSettingsEntry> entry, bool checked);
	virtual void setEntryLabelEnabled(QSharedPointer<QSettingsEntry> entry, bool enabled);
	virtual bool isEntryChecked(QSharedPointer<QSettingsEntry> entry) const;

	virtual bool searchExpression(const QRegularExpression &regex, const QString &searchStyleSheet);

protected:
	virtual void addWidgetWithLabel(QWidget *label, QWidget *content) = 0;

	typedef QPair<QWidget*, QSettingsWidgetBase*> GroupElement;
	QHash<QSharedPointer<QSettingsEntry>, GroupElement> entryMap;
};

template <class Widget>
class QSettingsGroupWidget : public Widget, public QSettingsGroupWidgetBase
{
public:
	inline QSettingsGroupWidget(QWidget *parent = nullptr) :
		Widget(parent),
		QSettingsGroupWidgetBase()
	{}

	inline QWidget *asWidget() final {
		return this;
	}
	void initialize(const QSettingsEntry::UiPropertyMap &uiPropertyMap) override {
		for(QSettingsEntry::UiPropertyMap::const_iterator it = uiPropertyMap.constBegin(), end = uiPropertyMap.constEnd(); it != end; ++it)
			this->setProperty(it.key().toLocal8Bit().constData(), it.value());
	}
};

#endif // QSETTINGSGROUPWIDGET_H
