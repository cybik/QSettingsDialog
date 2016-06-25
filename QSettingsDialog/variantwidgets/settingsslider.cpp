#include "settingsslider.h"
#include <QToolTip>
#include <QStyle>

SettingsSlider::SettingsSlider(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setOrientation(Qt::Horizontal);

	connect(this, &SettingsSlider::sliderPressed,
			this, &SettingsSlider::showValue,
			Qt::QueuedConnection);
	connect(this, &SettingsSlider::sliderMoved,
			this, &SettingsSlider::showValue,
			Qt::QueuedConnection);
}

void SettingsSlider::setValue(const QVariant &value)
{
	this->QSlider::setValue(value.toInt());
}

QVariant SettingsSlider::getValue() const
{
	return this->value();
}

void SettingsSlider::resetValue()
{
	this->QSlider::setValue(0);
}

void SettingsSlider::showValue()
{
	QPoint point;
	if(this->orientation() == Qt::Horizontal) {
		auto pos = QStyle::sliderPositionFromValue(this->minimum(),
												   this->maximum(),
												   this->value(),
												   this->width() -
												   this->style()->pixelMetric(QStyle::PM_SliderLength));
		point = QPoint(pos,
					   this->style()->pixelMetric(QStyle::PM_SliderLength));
	} else {
		auto pos = QStyle::sliderPositionFromValue(this->minimum(),
												   this->maximum(),
												   this->value(),
												   this->height() -
												   this->style()->pixelMetric(QStyle::PM_SliderLength),
												   true);
		point = QPoint(this->style()->pixelMetric(QStyle::PM_SliderThickness),
					   pos - this->style()->pixelMetric(QStyle::PM_SliderLength));
	}
	point = this->mapToGlobal(point);
	QToolTip::showText(point, QLocale().toString(this->value()), this);
}
