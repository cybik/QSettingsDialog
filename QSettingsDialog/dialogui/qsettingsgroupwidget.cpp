#include "qsettingsgroupwidget.h"
#include <QCheckBox>
#include <QLabel>
#include "settingsdisplaydialog.h"

QSettingsGroupWidgetBase::~QSettingsGroupWidgetBase() {}

void QSettingsGroupWidgetBase::addWidgetRaw(QSharedPointer<QSettingsEntry> entry, QWidget *content, bool hasError)
{
	QWidget *label = nullptr;
	if(entry->isOptional()) {
		auto optBox = new QCheckBox(this->asWidget());
		optBox->setText(entry->entryName() + SettingsDisplayDialog::tr(":"));
		QObject::connect(optBox, &QCheckBox::toggled,
						 content, &QWidget::setEnabled);
		label = optBox;
	} else {
		auto cLabel = new QLabel(this->asWidget());
		cLabel->setText(entry->entryName() + SettingsDisplayDialog::tr(":"));
		label = cLabel;
	}
	this->checkLabelMap.insert(entry.data(), label);

	label->setToolTip(entry->tooltip());
	if(content->toolTip().isNull())
		content->setToolTip(entry->tooltip());
	if(hasError)
		label->setEnabled(false);
	else
		content->setEnabled(!entry->isOptional());

	this->addWidgetWithLabel(label, content);
}

void QSettingsGroupWidgetBase::setEntryChecked(QSharedPointer<QSettingsEntry> entry, bool checked)
{
	auto box = dynamic_cast<QCheckBox*>(this->checkLabelMap.value(entry.data()));
	if(box)
		return box->setChecked(checked);
}

void QSettingsGroupWidgetBase::setEntryLabelEnabled(QSharedPointer<QSettingsEntry> entry, bool enabled)
{
	auto widget = this->checkLabelMap.value(entry.data());
	if(widget)
		widget->setEnabled(enabled);
}

bool QSettingsGroupWidgetBase::isEntryChecked(QSharedPointer<QSettingsEntry> entry) const
{
	auto box = dynamic_cast<QCheckBox*>(this->checkLabelMap.value(entry.data()));
	if(box)
		return box->isChecked();
	else
		return true;
}
