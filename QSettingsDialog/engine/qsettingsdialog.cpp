#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include "settingspathparser.h"
#include <QGlobalStatic>

#define d this->d_ptr

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}



QSettingsDialog::QSettingsDialog(QObject *parent) :
	QObject(parent),
	d_ptr(new QSettingsDialogPrivate(this))
{}

QSettingsDialog::~QSettingsDialog() {}

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
	Q_ASSERT(elements.size() == 3);
	d->categoryId = elements[0];
	d->sectionId = elements[1];
	d->groupId = elements[2];
}

bool QSettingsDialog::removeContainer(const QString &containerPath)
{
	auto elements = SettingsPathParser::parsePartialPath(containerPath);
	switch(elements.size()) {
	case 1:
		if(elements[0] == QStringLiteral(".")) {
			d->rootElement->defaultCategory.reset();
			return true;
		} else {
			d->rootElement->categories.remove(elements[0]);
			return d->rootElement->categoryOrder.removeOne(elements[0]);
		}
	case 2:
	{
		auto category = d->getCategory(elements[0]);
		if(elements[1] == QStringLiteral(".")) {
			category->defaultSection.reset();
			return true;
		} else {
			category->sections.remove(elements[1]);
			return category->sectionOrder.removeOne(elements[1]);
		}
	}
	case 3:
	{
		auto section = d->getSection(elements[1], elements[0]);
		if(elements[2] == QStringLiteral(".")) {
			section->defaultGroup.reset();
			return true;
		} else {
			section->groups.remove(elements[2]);
			return section->groupOrder.removeOne(elements[2]);
		}
	}
	default:
		Q_UNREACHABLE();
	}
}

int QSettingsDialog::appendEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, QSharedPointer<QSettingsEntry>(entry));
	group->entryOrder.append(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::appendEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	Q_ASSERT(elements.size() == 3);
	auto group = d->getGroup(elements[0], elements[1], elements[2]);
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, QSharedPointer<QSettingsEntry>(entry));
	group->entryOrder.append(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::prependEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, QSharedPointer<QSettingsEntry>(entry));
	group->entryOrder.prepend(d->currentIndexMax);
	return d->currentIndexMax;
}

int QSettingsDialog::prependEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	Q_ASSERT(elements.size() == 3);
	auto group = d->getGroup(elements[0], elements[1], elements[2]);
	Q_ASSERT(!group.isNull());

	group->entries.insert(++d->currentIndexMax, QSharedPointer<QSettingsEntry>(entry));
	group->entryOrder.prepend(d->currentIndexMax);
	return d->currentIndexMax;
}

QSettingsEntry *QSettingsDialog::getEntry(int id) const
{
	auto group = d->findEntryGroup(id);
	if(group.isNull())
		return nullptr;
	else
		return group->entries.value(id).data();
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

QString QSettingsDialog::createContainerPath(QString category, QString section, QString group)
{
	return SettingsPathParser::createPath(category, section, group);
}

QString QSettingsDialog::createContainerPath(QString category, QString section, QString group, bool escapeAll)
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

Q_GLOBAL_STATIC(QSettingsDialog, defaultDialogInstance)
QSettingsDialog *QSettingsDialog::defaultInstance()
{
	return defaultDialogInstance;
}

void QSettingsDialog::showSettings(QWidget *parentWindow)
{
	Q_UNIMPLEMENTED();
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
	currentIndexMax(0)
{}

QSharedPointer<SettingsCategory> QSettingsDialogPrivate::getCategory(QString categoryId)
{
	SettingsPathParser::validateId(categoryId, false);
	if(categoryId.isEmpty())
		categoryId = this->categoryId;

	if(categoryId == QLatin1String(".")) {
		if(this->rootElement->defaultCategory.isNull()) {
			this->rootElement->defaultCategory.reset(new SettingsCategory());
			//TODO setup default name/icon/tooltip
		}
		return this->rootElement->defaultCategory;
	} else {
		auto element = this->rootElement->categories.value(categoryId);
		if(element.isNull()) {
			element.reset(new SettingsCategory());
			this->rootElement->categories.insert(categoryId, element);
			this->rootElement->categoryOrder.append(categoryId);
		}
		return element;
	}
}

QSharedPointer<SettingsSection> QSettingsDialogPrivate::getSection(QString sectionId, const QString &categoryId)
{
	auto category = this->getCategory(categoryId);
	Q_ASSERT(!category.isNull());

	SettingsPathParser::validateId(sectionId, false);
	if(sectionId.isEmpty())
		sectionId = this->sectionId;

	if(sectionId == QLatin1String(".")) {
		if(category->defaultSection.isNull()) {
			category->defaultSection.reset(new SettingsSection());
			//TODO setup default name/icon/tooltip
		}
		return category->defaultSection;
	} else {
		auto element = category->sections.value(sectionId);
		if(element.isNull()) {
			element.reset(new SettingsSection());
			category->sections.insert(sectionId, element);
			category->sectionOrder.append(sectionId);
		}
		return element;
	}
}

QSharedPointer<SettingsGroup> QSettingsDialogPrivate::getGroup(QString groupId, const QString &sectionId, const QString &categoryId)
{
	auto section = this->getSection(sectionId, categoryId);
	Q_ASSERT(!section.isNull());

	SettingsPathParser::validateId(groupId, false);
	if(groupId.isEmpty())
		groupId = this->groupId;

	if(groupId == QLatin1String(".")) {
		if(section->defaultGroup.isNull()) {
			section->defaultGroup.reset(new SettingsGroup());
			//TODO setup default name/icon/tooltip
		}
		return section->defaultGroup;
	} else {
		auto element = section->groups.value(groupId);
		if(element.isNull()) {
			element.reset(new SettingsGroup());
			section->groups.insert(groupId, element);
			section->groupOrder.append(groupId);
		}
		return element;
	}
}

QString QSettingsDialogPrivate::findEntryPath(int id)
{
	auto categories = this->rootElement->categories;
	if(!this->rootElement->defaultCategory.isNull())
		categories.insert(QStringLiteral("."), this->rootElement->defaultCategory);

	for(QHash<QString, QSharedPointer<SettingsCategory>>::const_iterator categoryIt = categories.constBegin(),
		categoryEnd = categories.constEnd();
		categoryIt != categoryEnd;
		++categoryIt) {

		const QSharedPointer<SettingsCategory> &category = categoryIt.value();
		auto sections = category->sections;
		if(!category->defaultSection.isNull())
			sections.insert(QStringLiteral("."), category->defaultSection);

		for(QHash<QString, QSharedPointer<SettingsSection>>::const_iterator sectionIt = sections.constBegin(),
			sectionEnd = sections.constEnd();
			sectionIt != sectionEnd;
			++sectionIt) {

			const QSharedPointer<SettingsSection> &section = sectionIt.value();
			auto groups = section->groups;
			if(!section->defaultGroup.isNull())
				groups.insert(QStringLiteral("."), section->defaultGroup);

			for(QHash<QString, QSharedPointer<SettingsGroup>>::const_iterator groupIt = groups.constBegin(),
				groupEnd = groups.constEnd();
				groupIt != groupEnd;
				++groupIt) {

				const QSharedPointer<SettingsGroup> &group = groupIt.value();
				if(group->entries.contains(id)) {
					return SettingsPathParser::createPath(categoryIt.key(),
														  sectionIt.key(),
														  groupIt.key());
				}
			}

		}
	}

	return QString();
}

QSharedPointer<SettingsGroup> QSettingsDialogPrivate::findEntryGroup(int id)
{
	auto path = this->findEntryPath(id);
	if(path.isEmpty())
		return QSharedPointer<SettingsGroup>();
	else {
		auto elements = SettingsPathParser::parseFullPath(path);
		Q_ASSERT(elements.size() == 3);
		return this->getGroup(elements[0], elements[1], elements[2]);
	}
}
