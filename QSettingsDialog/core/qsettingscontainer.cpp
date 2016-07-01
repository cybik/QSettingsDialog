#include "qsettingscontainer.h"
#include "qsettingsdialog_p.h"
#include "containerelements.h"
#include "settingspathparser.h"
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


QSectionSettingsContainer::QSectionSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QSettingsContainer(parent),
	d_ptr(new QSectionSettingsContainerPrivate(this, settingsDialog, containerPath))
{
	connect(settingsDialog, &QSettingsDialog::destroyed, this, [this]() {//TODO ok so? not so beautiful
		d->dialog = nullptr;
	});
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

int QSectionSettingsContainer::getEntryId(int index) const
{
	auto id = d->section->groups.id(index);
	if(id.type() == QMetaType::Int)
		return id.toInt();
	else
		return -1;
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
		//HERE
	}
}

int QSectionSettingsContainer::appendEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.append(id, QSharedPointer<QSettingsEntry>(entry));
	return id;
}

int QSectionSettingsContainer::prependEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.prepend(id, QSharedPointer<QSettingsEntry>(entry));
	return id;
}

int QSectionSettingsContainer::insertEntry(int index, QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.insert(index, id, QSharedPointer<QSettingsEntry>(entry));
	return id;
}

int QSectionSettingsContainer::insertEntry(int index, QSharedPointer<QSettingsEntry> entry)
{
	auto id = d->dialog->getNextId();
	d->section->groups.insert(index, id, entry);
	return id;
}

bool QSectionSettingsContainer::removeEntry(int id)
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
	this->section = this->dialog->getSection(elements[2], elements[1]);
}
