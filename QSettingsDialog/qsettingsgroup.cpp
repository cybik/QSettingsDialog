#include "qsettingsgroup.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include "qsettingsentry.h"
#include "qsettingsdialog.h"

QSettingsGroup::QSettingsGroup(QGroupBox *box) :
	box(box),
	widget(Q_NULLPTR),
	layout(new QFormLayout(this->box)),
	entrs()
{
	this->box->setLayout(this->layout);
}

QSettingsGroup::QSettingsGroup(QWidget *widget) :
	box(Q_NULLPTR),
	widget(widget),
	layout(new QFormLayout(this->box)),
	entrs()
{
	this->widget->setLayout(this->layout);
	this->layout->setContentsMargins(0, 0, 0, 0);
}

QSettingsGroup::~QSettingsGroup()
{
	qDeleteAll(this->entrs);
}

bool QSettingsGroup::isActivated() const
{
	if(this->box && this->box->isCheckable())
		return this->box->isChecked();
	else
		return true;
}

QString QSettingsGroup::name() const
{
	if(this->box)
		return this->box->title();
	else
		return QString();
}

bool QSettingsGroup::isOptional() const
{
	if(this->box)
		return this->box->isCheckable();
	else
		return false;
}

void QSettingsGroup::setName(const QString &name)
{
	if(this->box)
		this->box->setTitle(name);
}

void QSettingsGroup::setOptional(bool optional)
{
	if(this->box) {
		this->box->setCheckable(optional);
		this->box->setChecked(!optional);
	}
}

QList<QSettingsEntry *> QSettingsGroup::entries() const
{
	return this->entrs;
}

QSettingsEntry *QSettingsGroup::entryAt(int index) const
{
	Q_ASSERT_X2(index >= 0 && index < this->entrs.size(), "index out of range");
	return this->entrs.at(index);
}

int QSettingsGroup::entryIndex(QSettingsEntry *entry) const
{
	return this->entrs.indexOf(entry);
}

void QSettingsGroup::insertEntry(int index, QSettingsEntry *entry)
{
	Q_ASSERT_X2(index >= 0 && index <= this->entrs.size(), "index out of range");

	QWidget *content = entry->createWidget(this->layout->widget())->asWidget();
	if(entry->isOptional()) {
		content->setEnabled(false);
		QCheckBox *box = new QCheckBox(entry->entryName() + QSettingsDialog::tr(":"),
									   this->layout->widget());
		QObject::connect(box, &QCheckBox::toggled,
						 content, &QWidget::setEnabled);
		this->layout->insertRow(index, box, content);
	} else {
		this->layout->insertRow(index,
								entry->entryName() + QSettingsDialog::tr(":"),
								content);
	}

	this->entrs.insert(index, entry);
}

QSettingsEntry *QSettingsGroup::takeEntry(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->entrs.size(), "index out of range");
	this->layout->itemAt(index, QFormLayout::LabelRole)->widget()->deleteLater();
	QSettingsEntry *entry = this->entrs.takeAt(index);
	QWidget *widget = this->layout->itemAt(index, QFormLayout::FieldRole)->widget();
	entry->destroyWidget(dynamic_cast<QSettingsWidgetBase*>(widget));
	return entry;
}

bool QSettingsGroup::takeEntry(QSettingsEntry *entry)
{
	int index = this->entrs.indexOf(entry);
	if(index >= 0) {
		this->takeEntry(index);
		return true;
	} else
		return false;
}

void QSettingsGroup::deleteEntry(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->entrs.size(), "index out of range");
	this->layout->itemAt(index, QFormLayout::LabelRole)->widget()->deleteLater();
	QSettingsEntry *entry = this->entrs.takeAt(index);
	QWidget *widget = this->layout->itemAt(index, QFormLayout::FieldRole)->widget();
	entry->destroyWidget(dynamic_cast<QSettingsWidgetBase*>(widget));
	delete entry;
}

bool QSettingsGroup::deleteEntry(QSettingsEntry *entry)
{
	int index = this->entrs.indexOf(entry);
	if(index >= 0) {
		this->deleteEntry(index);
		return true;
	} else
		return false;
}

void QSettingsGroup::moveEntry(int from, int to)
{
	Q_ASSERT_X2(from >= 0 && from < this->entrs.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to < this->entrs.size(), "index out of range");
	QWidget *labelWigdet = this->layout->itemAt(from, QFormLayout::LabelRole)->widget();
	QWidget *fieldWigdet = this->layout->itemAt(from, QFormLayout::FieldRole)->widget();
	this->layout->removeWidget(labelWigdet);
	this->layout->removeWidget(fieldWigdet);
	layout->insertRow(to, labelWigdet, fieldWigdet);
	this->entrs.move(from, to);
}
