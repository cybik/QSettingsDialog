#include "qsettingscontainerlayout.h"
#include "qsettingsdialog_p.h"
#include "qsettingscontainerlayout_p.h"
#include "settingspathparser.h"

#define d this->d_ptr

QSettingsContainerLayout QSettingsContainerLayout::dialogLayout(QSettingsDialog *settingsDialog)
{
	return QSettingsContainerLayout(new SettingsRootLayout(QString(), QSettingsDialogPrivate::getPrivateInstance(settingsDialog)->rootElement));
}

QString QSettingsContainerLayout::id() const
{
	return d->id;
}

QSettingsContainerLayout::LayoutType QSettingsContainerLayout::layoutType() const
{
	return d->layoutType;
}

bool QSettingsContainerLayout::isNull() const
{
	return d->testNull();
}

QString QSettingsContainerLayout::name() const
{
	return d->createNameRef();
}

void QSettingsContainerLayout::setName(const QString &name)
{
	d->createNameRef() = name;
}

QIcon QSettingsContainerLayout::icon() const
{
	return d->createIconRef();
}

void QSettingsContainerLayout::setIcon(const QIcon &icon)
{
	d->createIconRef() = icon;
}

QString QSettingsContainerLayout::tooltip() const
{
	return d->createTooltipRef();
}

void QSettingsContainerLayout::setTooltip(const QString &tooltip)
{
	d->createTooltipRef() = tooltip;
}

bool QSettingsContainerLayout::isOptional() const
{
	return d->createOptionalRef();
}

void QSettingsContainerLayout::setOptional(bool optional)
{
	d->createOptionalRef() = optional;
}

QSettingsContainerLayout QSettingsContainerLayout::defaultElement() const
{
	return d->creatDefaultElement();
}

int QSettingsContainerLayout::elementCount() const
{
	return d->elementCount();
}

QSettingsContainerLayout QSettingsContainerLayout::elementAt(int index) const
{
	return d->elementAt(index);
}

int QSettingsContainerLayout::indexOfElement(const QSettingsContainerLayout &element) const
{
	return d->indexOfElement(element);
}

QSettingsContainerLayout QSettingsContainerLayout::createOptionalElement(int index, const QString &id, const QString &name, bool optional, const QString &tooltip)
{
	SettingsPathParser::validateId(id, true);
	auto element = d->createEmptySubElement(id);
	element.setName(name.isNull() ? id : name);
	element.setOptional(optional);
	element.setTooltip(tooltip);
	d->insertElement(index, element);
	return element;
}

QSettingsContainerLayout QSettingsContainerLayout::createElement(int index, const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{
	SettingsPathParser::validateId(id, true);
	auto element = d->createEmptySubElement(id);
	element.setName(name.isNull() ? id : name);
	element.setIcon(icon);
	element.setTooltip(tooltip);
	d->insertElement(index, element);
	return element;
}

void QSettingsContainerLayout::removeElement(int index)
{
	d->removeElement(index);
}

void QSettingsContainerLayout::moveElement(int indexFrom, int indexTo)
{
	d->moveElement(indexFrom, indexTo);
}

QSettingsContainerLayout::QSettingsContainerLayout(QSettingsContainerLayoutPrivate *d_ptr) :
	d_ptr(d_ptr)
{}
