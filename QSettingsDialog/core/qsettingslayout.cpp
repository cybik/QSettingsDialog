#include "qsettingslayout.h"
#include "qsettingsdialog_p.h"
#include "qsettingslayout_p.h"
#include "settingspathparser.h"
#include "qsettingscontainer.h"

#define d this->d_ptr

QSettingsLayout::QSettingsLayout(QSettingsDialog *settingsDialog, bool fromCurrentContainer) :
	QSettingsLayout(settingsDialog, fromCurrentContainer ? settingsDialog->containerPath() : QString())
{}

QSettingsLayout::QSettingsLayout(QSettingsDialog *settingsDialog, const QString &containerPath, int entryId) :
	d_ptr()
{
	auto privDiag = QSettingsDialogPrivate::getPrivateInstance(settingsDialog);
	if(containerPath.isNull())
		d.reset(new SettingsRootLayout(QString(), privDiag->rootElement, settingsDialog));
	else {
		auto elements = SettingsPathParser::parsePartialPath(containerPath);
		switch(elements.size()) {
		case 1:
			d.reset(new SettingsCategoryLayout(elements[0], privDiag->getCategory(elements[0]), settingsDialog));
			break;
		case 2:
			if(entryId == -1)
				d.reset(new SettingsSectionLayout(elements[1], privDiag->getSection(elements[1], elements[0]), settingsDialog));
			else
				d.reset(new SettingsEntryLayout(entryId, privDiag->getSection(elements[1], elements[0])->groups.valueId(entryId), settingsDialog));
			break;
		case 3:
			if(entryId == -1)
				d.reset(new SettingsGroupLayout(elements[2], privDiag->getGroup(elements[2], elements[1], elements[0]), settingsDialog));
			else
				d.reset(new SettingsEntryLayout(entryId, privDiag->getGroup(elements[2], elements[1], elements[0])->entries.valueId(entryId), settingsDialog));
			break;
		}
	}
}

QSettingsLayout::QSettingsLayout(QSettingsContainer *container) :
	QSettingsLayout(container->dialog(), container->containerPath())
{}

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
	return !d || d->testNull();
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
	auto parent = QSettingsLayout((QSettingsLayoutPrivate*)nullptr);
	if(!d->parentElement.isNull())
		parent.d_ptr = d->parentElement;
	return parent;
}

int QSettingsLayout::displayId() const
{
	return d->createDisplayIdRef();
}

void QSettingsLayout::setDisplayId(int displayId)
{
	d->createDisplayIdRef() = displayId;
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

bool QSettingsLayout::removeDefaultElement()
{
	return d->removeDefaultElement();
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
	return d->indexOfElement(element.id());
}

int QSettingsLayout::indexOfElement(const QString &elementName) const
{
	return d->indexOfElement(elementName);
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

QSettingsLayout QSettingsLayout::createGroupElement(int index, const QString &id, int displayId, const QString &name, bool optional, const QString &tooltip)
{
	SettingsPathParser::validateId(id, true);
	auto element = d->createEmptySubElement(id);
	element.d_ptr->parentElement = this->d_ptr;
	element.setDisplayId(displayId);
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
