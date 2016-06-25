#include "qsettingsdialogwidget.h"
#include <QPushButton>
#include <QHBoxLayout>

QSettingsDialogWidgetBase::QSettingsDialogWidgetBase(QWidget *parent) :
	QSettingsWidget(parent),
	btn(new QPushButton(this))
{
	this->btn->setAutoDefault(false);
	this->btn->setDefault(false);

	connect(this->btn, &QPushButton::clicked,
			this, &QSettingsDialogWidgetBase::showDialog);

	auto layout = new QHBoxLayout(this);
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(this->btn);
	layout->addStretch();
	this->setLayout(layout);
}

QIcon QSettingsDialogWidgetBase::buttonIcon() const
{
	return QIcon();
}

void QSettingsDialogWidgetBase::showEvent(QShowEvent *event)
{
	this->btn->setText(this->buttonText());
	this->btn->setIcon(this->buttonIcon());
	this->QWidget::showEvent(event);
}
