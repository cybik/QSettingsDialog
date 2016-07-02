#include "qsettingscontainer.h"
#include "qsettingsdialog_p.h"
#include "containerelements.h"
#include "settingspathparser.h"
#include "qsettingslayout.h"
#include <QSharedPointer>

#define d this->d_ptr

class QSectionSettingsContainerPrivate
{
public:
	QSectionSettingsContainerPrivate(QSectionSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath);

	QSectionSettingsContainer *q_ptr;
	QSettingsDialogPrivate *dialog;
	QString containerPath;

	QSharedPointer<SettingsSection> section;
};

class QGroupSettingsContainerPrivate
{
public:
	QGroupSettingsContainerPrivate(QGroupSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath);

	QGroupSettingsContainer *q_ptr;
	QSettingsDialogPrivate *dialog;
	QString containerPath;

	QSharedPointer<SettingsGroup> group;
};



QGroupSettingsContainer::QGroupSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QSettingsContainer(parent),
	d_ptr(new QGroupSettingsContainerPrivate(this, settingsDialog, containerPath))
{
	connect(settingsDialog, &QSettingsDialog::destroyed, this, [this]() {//TODO ok so? not so beautiful
		d->dialog = nullptr;
	}, Qt::DirectConnection);
}

QGroupSettingsContainer::~QGroupSettingsContainer() {}

QSettingsDialog *QGroupSettingsContainer::dialog() const
{
	return d->dialog->q_ptr;
}

QString QGroupSettingsContainer::containerPath() const
{
	return d->containerPath;
}

int QGroupSettingsContainer::elementCount() const
{
	return d->group->entries.size();
}

bool QGroupSettingsContainer::isEntry(int) const
{
	return true;
}

int QGroupSettingsContainer::getEntryIndex(int id) const
{
	return d->group->entries.index(id);
}

int QGroupSettingsContainer::getEntryId(int index) const
{
	return d->group->entries.id(index);
}

QSharedPointer<QSettingsEntry> QGroupSettingsContainer::getEntry(int id) const
{
	return d->group->entries.valueId(id);
}

QSharedPointer<QSettingsEntry> QGroupSettingsContainer::getEntryFromIndex(int index) const
{
	return d->group->entries.value(index);
}

bool QGroupSettingsContainer::transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo)
{
	auto element = d->group->entries.entry(indexFrom);
	auto ok = this->doAccept(targetContainer, indexTo, element.first, element.second);
	if(ok)
		d->group->entries.remove(indexFrom);
	return ok;
}

QSectionSettingsContainer *QGroupSettingsContainer::parentSection()
{
	auto elements = SettingsPathParser::parseFullPath(d->containerPath);
	return new QSectionSettingsContainer(d->dialog->q_ptr, SettingsPathParser::createPath(elements[0], elements[1]), this);
}

QSectionSettingsContainer *QGroupSettingsContainer::parentSection(QObject *parent) const
{
	auto elements = SettingsPathParser::parseFullPath(d->containerPath);
	return new QSectionSettingsContainer(d->dialog->q_ptr, SettingsPathParser::createPath(elements[0], elements[1]), parent);
}

int QGroupSettingsContainer::appendEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.append(id, entry);
	return id;
}

int QGroupSettingsContainer::prependEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.prepend(id, entry);
	return id;
}

int QGroupSettingsContainer::insertEntry(int index, QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.insert(index, id, entry);
	return id;
}

int QGroupSettingsContainer::insertEntry(int index, QSharedPointer<QSettingsEntry> entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.insert(index, id, entry);
	return id;
}

bool QGroupSettingsContainer::removeEntry(int id)
{
	return d->group->entries.removeId(id);
}

bool QGroupSettingsContainer::removeElementFromIndex(int index)
{
	return d->group->entries.remove(index);
}

void QGroupSettingsContainer::moveElement(int indexFrom, int indexTo)
{
	d->group->entries.move(indexFrom, indexTo);
}

bool QGroupSettingsContainer::acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry)
{
	d->group->entries.insert(index, id, entry);
	return true;
}



QSectionSettingsContainer::QSectionSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QSettingsContainer(parent),
	d_ptr(new QSectionSettingsContainerPrivate(this, settingsDialog, containerPath))
{
	connect(settingsDialog, &QSettingsDialog::destroyed, this, [this]() {//TODO ok so? not so beautiful
		d->dialog = nullptr;
	}, Qt::DirectConnection);
}

QSectionSettingsContainer::QSectionSettingsContainer(QSettingsLayout *layout, QObject *parent) :
	QSettingsContainer(parent),
	d_ptr()
{
	if(layout->layoutType() != QSettingsLayout::SectionLayout)
		throw InvalidTargetLayoutException();

	auto dialog = layout->dialog();
	d.reset(new QSectionSettingsContainerPrivate(this, dialog, layout->containerPath()));
	connect(dialog, &QSettingsDialog::destroyed, this, [this]() {//TODO ok so? not so beautiful
		d->dialog = nullptr;
	}, Qt::DirectConnection);
}

QSectionSettingsContainer::~QSectionSettingsContainer() {}

QSettingsDialog *QSectionSettingsContainer::dialog() const
{
	return d->dialog->q_ptr;
}

QString QSectionSettingsContainer::containerPath() const
{
	return d->containerPath;
}

int QSectionSettingsContainer::elementCount() const
{
	return d->section->groups.size();
}

bool QSectionSettingsContainer::isEntry(int index) const
{
	return d->section->groups.id(index).type() == QMetaType::Int;
}

int QSectionSettingsContainer::getEntryIndex(int id) const
{
	return d->section->groups.index(id);
}

int QSectionSettingsContainer::getGroupIndex(const QString &id) const
{
	return d->section->groups.index(id);
}

QVariant QSectionSettingsContainer::getElementId(int index) const
{
	return d->section->groups.id(index);
}

int QSectionSettingsContainer::getEntryId(int index) const
{
	auto id = d->section->groups.id(index);
	if(id.type() == QMetaType::Int)
		return id.toInt();
	else
		return -1;
}

QString QSectionSettingsContainer::getGrouptId(int index) const
{
	auto id = d->section->groups.id(index);
	if(id.type() == QMetaType::QString)
		return id.toString();
	else
		return QString();
}

QSharedPointer<QSettingsEntry> QSectionSettingsContainer::getEntry(int id) const
{
	return d->section->groups.valueId(id);
}

QSharedPointer<QSettingsEntry> QSectionSettingsContainer::getEntryFromIndex(int index) const
{
	auto element = d->section->groups.entry(index);
	if(element.first.type() == QMetaType::Int)
		return element.second.second;
	else
		return QSharedPointer<QSettingsEntry>();
}

bool QSectionSettingsContainer::transferElement(int indexFrom, QSettingsContainer *targetContainer, int indexTo)
{
	auto element = d->section->groups.entry(indexFrom);
	if(element.first.type() == QMetaType::Int) {
		auto ok = this->doAccept(targetContainer, indexTo, element.first.toInt(), element.second.second);
		if(ok)
			d->section->groups.remove(indexFrom);
		return ok;
	} else {
		auto asSect = qobject_cast<QSectionSettingsContainer*>(targetContainer);
		asSect->d_ptr->section->groups.insert(indexTo, element.first.toString(), element.second.first);
		return true;
	}
}

QGroupSettingsContainer *QSectionSettingsContainer::createGroupContainer(const QString &id)
{
	auto group = d->section->groups.valueId(id);
	if(group.isNull())
		return nullptr;
	else
		return new QGroupSettingsContainer(d->dialog->q_ptr, SettingsPathParser::joinPath(d->containerPath, id), this);
}

QGroupSettingsContainer *QSectionSettingsContainer::createGroupContainer(const QString &id, QObject *parent) const
{
	auto group = d->section->groups.valueId(id);
	if(group.isNull())
		return nullptr;
	else
		return new QGroupSettingsContainer(d->dialog->q_ptr, SettingsPathParser::joinPath(d->containerPath, id), parent);
}

QGroupSettingsContainer *QSectionSettingsContainer::createGroupContainerFromIndex(int index)
{
	auto entry = d->section->groups.entry(index);
	if(entry.first.type() == QMetaType::QString)
		return new QGroupSettingsContainer(d->dialog->q_ptr, SettingsPathParser::joinPath(d->containerPath, entry.first.toString()), this);
	else
		return nullptr;
}

QGroupSettingsContainer *QSectionSettingsContainer::createGroupContainerFromIndex(int index, QObject *parent) const
{
	auto entryId = d->section->groups.id(index);
	if(entryId.type() == QMetaType::QString)
		return new QGroupSettingsContainer(d->dialog->q_ptr, SettingsPathParser::joinPath(d->containerPath, entryId.toString()), parent);
	else
		return nullptr;
}

int QSectionSettingsContainer::appendEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.append(id, entry);
	return id;
}

int QSectionSettingsContainer::prependEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.prepend(id, entry);
	return id;
}

int QSectionSettingsContainer::insertEntry(int index, QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.insert(index, id, entry);
	return id;
}

int QSectionSettingsContainer::insertEntry(int index, QSharedPointer<QSettingsEntry> entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.insert(index, id, entry);
	return id;
}

void QSectionSettingsContainer::appendGroup(const QString &id, const QString &name)
{
	SettingsPathParser::validateId(id, false);
	d->section->groups.append(id, new SettingsGroup(name.isNull() ? id : name));
}

void QSectionSettingsContainer::prependGroup(const QString &id, const QString &name)
{
	SettingsPathParser::validateId(id, false);
	d->section->groups.prepend(id, new SettingsGroup(name.isNull() ? id : name));
}

void QSectionSettingsContainer::insertGroup(int index, const QString &id, const QString &name)
{
	SettingsPathParser::validateId(id, false);
	d->section->groups.insert(index, id, new SettingsGroup(name.isNull() ? id : name));
}

bool QSectionSettingsContainer::removeEntry(int id)
{
	return d->section->groups.removeId(id);
}

bool QSectionSettingsContainer::removeGroup(const QString &id)
{
	return d->section->groups.removeId(id);
}

bool QSectionSettingsContainer::removeElementFromIndex(int index)
{
	return d->section->groups.remove(index);
}

void QSectionSettingsContainer::moveElement(int indexFrom, int indexTo)
{
	d->section->groups.move(indexFrom, indexTo);
}

bool QSectionSettingsContainer::acceptEntry(int index, int id, QSharedPointer<QSettingsEntry> entry)
{
	d->section->groups.insert(index, id, entry);
	return true;
}



QSectionSettingsContainerPrivate::QSectionSettingsContainerPrivate(QSectionSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath) :
	q_ptr(q_ptr),
	dialog(QSettingsDialogPrivate::getPrivateInstance(settingsDialog)),
	containerPath(containerPath),
	section()
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	if(elements.size() != 2)
		throw InvalidContainerPathException();
	this->section = this->dialog->getSection(elements[1], elements[0]);
}

QGroupSettingsContainerPrivate::QGroupSettingsContainerPrivate(QGroupSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath) :
	q_ptr(q_ptr),
	dialog(QSettingsDialogPrivate::getPrivateInstance(settingsDialog)),
	containerPath(containerPath),
	group()
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	if(elements.size() != 3)
		throw InvalidContainerPathException();
	this->group = this->dialog->getGroup(elements[2], elements[1], elements[0]);
}
