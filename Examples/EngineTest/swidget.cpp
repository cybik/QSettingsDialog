#include "swidget.h"

SWidget::SWidget(QWidget *parent, bool ttip, QString pattern) :
	QSettingsWidget(parent),
	pattern(pattern)
{
	if(ttip)
		this->setToolTip("Mikeichalt");
}

void SWidget::setValue(const QVariant &value)
{
	this->setText(value.toString());
}

QVariant SWidget::getValue() const
{
	return this->text();
}

void SWidget::resetValue()
{
	this->clear();
}

bool SWidget::searchExpression(const QRegularExpression &regex)
{
	return regex.match(pattern).hasMatch();
}



SFactory::SFactory(bool isDelayed) :
	isDelayed(isDelayed)
{}

QSettingsWidgetBase *SFactory::createWidget(QWidget *parent)
{
	if(this->isDelayed)
		return new SWidget(parent, true, "qu");
	else
		return new SWidget(parent, false);
}
