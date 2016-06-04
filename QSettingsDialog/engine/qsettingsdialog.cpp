#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include "settingspathparser.h"

#define d this->d_ptr

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}



QSettingsDialog::QSettingsDialog(QObject *parent) :
	QObject(parent),
	d_ptr(new QSettingsDialogPrivate(this))
{}

QSettingsDialogLayout *QSettingsDialog::layout()
{
	Q_UNIMPLEMENTED();
	return nullptr;
}

QString QSettingsDialog::containerPath() const
{
	return SettingsPathParser::createPath(d->categoryId, d->sectionId, d->groupId);
}

QString QSettingsDialog::categoryId() const
{
	return d->categoryId;
}

QString QSettingsDialog::sectionId() const
{
	return d->sectionId;
}

QString QSettingsDialog::groupId() const
{
	return d->groupId;
}

void QSettingsDialog::setCategory(const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{
	auto element = d->getCategory(id);
	Q_ASSERT(!element.isNull());
	d->categoryId = id;

	if(!name.isNull())
		element->name = name;
	if(!icon.isNull())
		element->icon = icon;
	if(!tooltip.isNull())
		element->tooltip = tooltip;
}

void QSettingsDialog::setSection(const QString &id, const QString &name, const QIcon &icon, const QString &tooltip)
{
	auto element = d->getSection(id);
	Q_ASSERT(!element.isNull());
	d->sectionId = id;

	if(!name.isNull())
		element->name = name;
	if(!icon.isNull())
		element->icon = icon;
	if(!tooltip.isNull())
		element->tooltip = tooltip;
}

void QSettingsDialog::setGroup(const QString &id, const QString &name, bool optional, const QString &tooltip)
{
	auto element = d->getGroup(id);
	Q_ASSERT(!element.isNull());
	d->groupId = id;

	if(!name.isNull())
		element->name = name;
	if(!tooltip.isNull())
		element->tooltip = tooltip;
	element->isOptional = optional;
}

void QSettingsDialog::setContainer(const QString &containerPath)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	d->categoryId = elements[0];
	d->sectionId = elements[1];
	d->groupId = elements[2];
}

int QSettingsDialog::appendEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, entry);
	group->entryOrder.append(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::appendEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	auto group = d->getGroup(elements[0], elements[1], elements[2]);
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, entry);
	group->entryOrder.append(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::prependEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, entry);
	group->entryOrder.prepend(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::prependEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	auto group = d->getGroup(elements[0], elements[1], elements[2]);
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, entry);
	group->entryOrder.prepend(d->currentIndexMax);
	return d->currentIndexMax;
}

QSettingsEntry *QSettingsDialog::getEntry(int id) const
{
	auto group = d->findEntryGroup(id);
	if(group.isNull())
		return nullptr;
	else
		return group->entries.value(id);
}

QString QSettingsDialog::getEntryPath(int id) const
{
	return d->findEntryPath(id);
}

bool QSettingsDialog::removeEntry(int id)
{
	auto group = d->findEntryGroup(id);
	if(group.isNull())
		return false;
	else {
		group->entries.remove(id);
		return group->entryOrder.removeOne(id);
	}
}

QString QSettingsDialog::createContainerPath(const QString &category, const QString &section, const QString &group, bool escapeAll)
{
	if(escapeAll) {
		if(category.isEmpty())
			category = d->categoryId;
		if(section.isEmpty())
			section = d->sectionId;
		if(group.isEmpty())
			group = d->groupId;
	}

	return SettingsPathParser::createPath(category, section, group);
}



QSettingsDialogPrivate *QSettingsDialogPrivate::getPrivateInstance(QSettingsDialog *dialog)
{
	return dialog->d_ptr.data();
}

QSettingsDialogPrivate::QSettingsDialogPrivate(QSettingsDialog *q_ptr) :
	q_ptr(q_ptr),
	rootElement(),
	categoryId(QStringLiteral(".")),
	sectionId(QStringLiteral(".")),
	groupId(QStringLiteral(".")),
	currentIndexMax(0),
	entryMap()
{}

QSharedPointer<SettingsCategory> QSettingsDialogPrivate::getCategory(const QString &id)
{

}

QSharedPointer<SettingsSection> QSettingsDialogPrivate::getSection(const QString &sectionId, const QString &categoryId)
{

}

QSharedPointer<SettingsGroup> QSettingsDialogPrivate::getGroup(const QString &groupId, const QString &sectionId, const QString &categoryId)
{

}
