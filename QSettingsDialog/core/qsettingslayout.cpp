#include "qsettingslayout.h"
#include "qsettingsdialog_p.h"
#include "qsettingslayout_p.h"
#include "settingspathparser.h"

#define d this->d_ptr

QSettingsLayout QSettingsLayout::dialogLayout(QSettingsDialog *settingsDialog)
{
	return QSettingsLayout(new SettingsRootLayout(QString(), QSettingsDialogPrivate::getPrivateInstance(settingsDialog)->rootElement, settingsDialog));
}

QString QSettingsLayout::id() const
{
	return d->id;
}

QSettingsLayout::LayoutType QSettingsLayout::layoutType() const
{
	return d->layoutType;
}

bool QSettingsLayout::isNull() const
{
	return d->testNull();
}

QSettingsDialog *QSettingsLayout::dialog() const
{
	return d->dialog;
}

QString QSettingsLayout::containerPath() const
{
	return d->createIdPath();
}

QSettingsLayout QSettingsLayout::parentContainer() const
{
	auto parent = QSettingsLayout(nullptr);
	if(d->parentElement.isNull())
		throw InvalidTargetLayoutException();
	parent.d_ptr = d->parentElement;
	return parent;
}

QString QSettingsLayout::name() const
{
	return d->createNameRef();
}

void QSettingsLayout::setName(const QString &name)
{
	d->createNameRef() = name;
}

QIcon QSettingsLayout::icon() const
{
	return d->createIconRef();
}

void QSettingsLayout::setIcon(const QIcon &icon)
{
	d->createIconRef() = icon;
}

QString QSettingsLayout::tooltip() const
{
	return d->createTooltipRef();
}

void QSettingsLayout::setTooltip(const QString &tooltip)
{
	d->createTooltipRef() = tooltip;
}

bool QSettingsLayout::isOptional() const
{
	return d->createOptionalRef();
}

void QSettingsLayout::setOptional(bool optional)
{
	d->createOptionalRef() = optional;
}

QSettingsLayout QSettingsLayout::defaultElement(bool allowCreateNew) const
{
	auto element = d->creatDefaultElement(allowCreateNew);
	element.d_ptr->parentElement = this->d_ptr;
	return element;
}

int QSettingsLayout::elementCount() const
{
	return d->elementCount();
}

QSettingsLayout QSettingsLayout::elementAt(int index) const
{
	auto element = d->elementAt(index);
	element.d_ptr->parentElement = this->d_ptr;
	return element;
}

int QSettingsLayout::indexOfElement(const QSettingsLayout &element) const
{
	return d->indexOfElement(element);
}

QSettingsLayout QSettingsLayout::createElement(int index, const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{
	SettingsPathParser::validateId(id, true);
	auto element = d->createEmptySubElement(id);
	element.d_ptr->parentElement = this->d_ptr;
	element.setName(name.isNull() ? id : name);
	element.setIcon(icon);
	element.setTooltip(tooltip);
	d->insertElement(index, element);
	return element;
}

QSettingsLayout QSettingsLayout::createOptionalElement(int index, const QString &id, const QString &name, bool optional, const QString &tooltip)
{
	SettingsPathParser::validateId(id, true);
	auto element = d->createEmptySubElement(id);
	element.d_ptr->parentElement = this->d_ptr;
	element.setName(name.isNull() ? id : name);
	element.setOptional(optional);
	element.setTooltip(tooltip);
	d->insertElement(index, element);
	return element;
}

void QSettingsLayout::removeElement(int index)
{
	auto element = d->elementAt(index);
	element.d_ptr->parentElement.clear();
	d->removeElement(index);
}

void QSettingsLayout::moveElement(int indexFrom, int indexTo)
{
	d->moveElement(indexFrom, indexTo);
}

void QSettingsLayout::transferElement(int indexFrom, QSettingsLayout targetLayout, int indexTo)
{
	if(targetLayout.isNull() || targetLayout.layoutType() != this->layoutType())
		throw InvalidTargetLayoutException();
	auto element = d->elementAt(indexFrom);
	d->removeElement(indexFrom);
	element.d_ptr->parentElement = targetLayout.d_ptr;
	targetLayout.d_ptr->insertElement(indexTo, element);
}

QSettingsLayout::QSettingsLayout(QSettingsLayoutPrivate *d_ptr) :
	d_ptr(d_ptr)
{}

QString QSettingsLayoutPrivate::createIdPath() const
{
	QString pathBase;
	if(!this->parentElement.isNull()) {
		pathBase = this->parentElement->createIdPath();
		if(!pathBase.isEmpty())
			pathBase += QLatin1Char('/');
	}
	return pathBase + this->id;
}
