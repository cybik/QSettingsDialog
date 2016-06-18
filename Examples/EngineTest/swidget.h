#ifndef SWIDGET_H
#define SWIDGET_H

#include <qsettingswidgetfactory.h>
#include <QLineEdit>

class SFactory : public QSettingsWidgetFactory
{
public:
	SFactory(bool isDelayed);
	QSettingsWidgetBase *createWidget(QWidget *parent) override;

private:
	bool isDelayed;
};

class SWidget : public QSettingsWidget<QLineEdit>
{
public:
	SWidget(QWidget *parent, bool ttip, QString pattern = QString());

	void setValue(const QVariant &value) override;
	QVariant getValue() const override;
	void resetValue() override;
	bool searchExpression(const QRegularExpression &regex) override;

private:
	QString pattern;
};

#endif // SWIDGET_H
