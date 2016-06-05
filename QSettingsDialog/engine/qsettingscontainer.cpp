#include "qsettingscontainer.h"
#include "qsettingsdialog_p.h"
#include "containerelements.h"
#include "settingspathparser.h"
#include <QSharedPointer>

#define d this->d_ptr

class QSettingsContainerPrivate
{
public:
	QSettingsContainerPrivate(QSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath);

	QSettingsContainer *q_ptr;
	QSettingsDialogPrivate *dialog;
	QString containerPath;
	QSharedPointer<SettingsGroup> group;
};

QSettingsContainer::QSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QObject(parent),
	d_ptr(new QSettingsContainerPrivate(this, settingsDialog,containerPath))
{
	connect(settingsDialog, &QSettingsDialog::destroyed,
			this, &QSettingsContainer::deleteLater);
}

QSettingsContainer::~QSettingsContainer() {}

int QSettingsContainer::appendEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.append(id, entry);
	return id;
}

int QSettingsContainer::prependEntry(QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.prepend(id, entry);
	return id;
}

int QSettingsContainer::insertEntry(int index, QSettingsEntry *entry)
{
	auto id = d->dialog->getNextId();
	d->group->entries.insert(index, id, entry);
	return id;
}

int QSettingsContainer::getEntryIndex(int id) const
{
	return d->group->entries.index(id);
}

int QSettingsContainer::getEntryId(int index) const
{
	return d->group->entries.id(index);
}

QSettingsEntry *QSettingsContainer::getEntry(int id) const
{
	return d->group->entries.valueId(id).data();
}

QSettingsEntry *QSettingsContainer::getEntryFromIndex(int index) const
{
	return d->group->entries.value(index).data();
}

bool QSettingsContainer::removeEntry(int id)
{
	return d->group->entries.removeId(id);
}

bool QSettingsContainer::removeEntryFromIndex(int index)
{
	return d->group->entries.remove(index);
}

void QSettingsContainer::moveEntry(int indexFrom, int indexTo)
{
	return d->group->entries.move(indexFrom, indexTo);
}



QAsyncSettingsContainer::QAsyncSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QSettingsContainer(settingsDialog, containerPath, parent)
{
	Q_ASSERT_X(this->thread() == settingsDialog->thread(), Q_FUNC_INFO, "The container must be created on the same thread as the dialog");
	if(!d->group->locker.testAndSetOrdered(nullptr, this))
		throw ContainerLockedException();
}

QAsyncSettingsContainer::~QAsyncSettingsContainer()
{
	d->group->locker.testAndSetOrdered(this, nullptr);
}



QSettingsContainerPrivate::QSettingsContainerPrivate(QSettingsContainer *q_ptr, QSettingsDialog *settingsDialog, const QString &containerPath) :
	q_ptr(q_ptr),
	dialog(QSettingsDialogPrivate::getPrivateInstance(settingsDialog)),
	containerPath(containerPath),
	group()
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	this->group = this->dialog->getGroup(elements[2], elements[1], elements[0]);
}
