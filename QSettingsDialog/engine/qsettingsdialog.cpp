#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"
#include "settingspathparser.h"
#include "settingsdisplaydialog.h"
#include <QGlobalStatic>

#define d this->d_ptr

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
		} else
			return d->rootElement->categories.removeId(elements[0]);
	case 2:
	{
		auto category = d->getCategory(elements[0]);
		if(elements[1] == QStringLiteral(".")) {
			category->defaultSection.reset();
			return true;
		} else
			return category->sections.removeId(elements[1]);
	}
	case 3:
	{
		auto section = d->getSection(elements[1], elements[0]);
		if(elements[2] == QStringLiteral(".")) {
			section->defaultGroup.reset();
			return true;
		} else
			return section->groups.removeId(elements[2]);
	}
	default:
		Q_UNREACHABLE();
	}
}

int QSettingsDialog::appendEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());
	group->testNotLocked();

	auto id = d->getNextId();
	group->entries.append(id, entry);
	return id;
}

int QSettingsDialog::appendEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	Q_ASSERT(elements.size() == 3);
	auto group = d->getGroup(elements[2], elements[1], elements[0]);
	Q_ASSERT(!group.isNull());
	group->testNotLocked();

	auto id = d->getNextId();
	group->entries.append(id, entry);
	return id;
}

int QSettingsDialog::prependEntry(QSettingsEntry *entry)
{
	auto group = d->getGroup();
	Q_ASSERT(!group.isNull());
	group->testNotLocked();

	auto id = d->getNextId();
	group->entries.prepend(id, entry);
	return id;
}

int QSettingsDialog::prependEntry(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);
	Q_ASSERT(elements.size() == 3);
	auto group = d->getGroup(elements[2], elements[1], elements[0]);
	Q_ASSERT(!group.isNull());
	group->testNotLocked();

	auto id = d->getNextId();
	group->entries.prepend(id, entry);
	return id;
}

int QSettingsDialog::appendEntryAsGroup(QSettingsEntry *entry)
{
	auto section = d->getSection();
	Q_ASSERT(!section.isNull());

	auto id = d->getNextId();
	section->groups.append(id, entry);
	return id;
}

int QSettingsDialog::appendEntryAsGroup(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseSectionPath(containerPath);
	Q_ASSERT(elements.size() == 2);
	auto section = d->getSection(elements[1], elements[0]);
	Q_ASSERT(!section.isNull());

	auto id = d->getNextId();
	section->groups.append(id, entry);
	return id;
}

int QSettingsDialog::prependEntryAsGroup(QSettingsEntry *entry)
{
	auto section = d->getSection();
	Q_ASSERT(!section.isNull());

	auto id = d->getNextId();
	section->groups.prepend(id, entry);
	return id;
}

int QSettingsDialog::prependEntryAsGroup(const QString &containerPath, QSettingsEntry *entry)
{
	auto elements = SettingsPathParser::parseSectionPath(containerPath);
	Q_ASSERT(elements.size() == 2);
	auto section = d->getSection(elements[1], elements[0]);
	Q_ASSERT(!section.isNull());

	auto id = d->getNextId();
	section->groups.prepend(id, entry);
	return id;
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
	else
		return group->entries.removeId(id);
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
	SettingsDisplayDialog dialog(parentWindow);
	dialog.createUi(d->rootElement);
	dialog.exec();
	emit resetted();
}



QSettingsDialogPrivate *QSettingsDialogPrivate::getPrivateInstance(QSettingsDialog *dialog)
{
	return dialog->d_ptr.data();
}

int QSettingsDialogPrivate::getNextId()
{
	return ++this->currentIdMax;
}

QSettingsDialogPrivate::QSettingsDialogPrivate(QSettingsDialog *q_ptr) :
	q_ptr(q_ptr),
	rootElement(new SettingsRoot()),
	categoryId(QStringLiteral(".")),
	sectionId(QStringLiteral(".")),
	groupId(QStringLiteral(".")),
	currentIdMax(0)
{}

QSharedPointer<SettingsCategory> QSettingsDialogPrivate::getCategory(QString categoryId)
{
	SettingsPathParser::validateId(categoryId, false);
	if(categoryId.isEmpty())
		categoryId = this->categoryId;

	if(categoryId == QLatin1String(".")) {
		if(this->rootElement->defaultCategory.isNull()) {
			auto cat = new SettingsCategory();
			cat->name = QSettingsDialog::tr("General Settings");
			cat->icon = QIcon(QStringLiteral(":/QSettingsDialog/icons/settings.ico"));
			this->rootElement->defaultCategory.reset(cat);
		}
		return this->rootElement->defaultCategory;
	} else {
		auto element = this->rootElement->categories.valueId(categoryId);
		if(element.isNull())
			element = this->rootElement->categories.append(categoryId, new SettingsCategory());
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
			auto sect = new SettingsSection();
			sect->name = QSettingsDialog::tr("General");
			category->defaultSection.reset(sect);
		}
		return category->defaultSection;
	} else {
		auto element = category->sections.valueId(sectionId);
		if(element.isNull())
			element = category->sections.append(sectionId, new SettingsSection());
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
			auto grp = new SettingsGroup();
			grp->name = QSettingsDialog::tr("General");
			section->defaultGroup.reset(grp);
		}
		return section->defaultGroup;
	} else {
		auto element = section->groups.valueId(groupId);
		if(element.isNull())
			element = section->groups.append(groupId, new SettingsGroup());
		return element;
	}
}

QString QSettingsDialogPrivate::findEntryPath(int id)
{
	auto categories = this->rootElement->categories;
	if(!this->rootElement->defaultCategory.isNull())
		categories.append(QStringLiteral("."), this->rootElement->defaultCategory);

	foreach(auto categoryElement, categories) {
		const QSharedPointer<SettingsCategory> &category = categoryElement.second;

		auto sections = category->sections;
		if(!category->defaultSection.isNull())
			sections.append(QStringLiteral("."), category->defaultSection);

		foreach(auto sectionElement, sections) {
			const QSharedPointer<SettingsSection> &section = sectionElement.second;

			if(section->groups.contains(id)) {
				//TODO only 2 elements
				return SettingsPathParser::createPath(categoryElement.first,
													  sectionElement.first,
													  QString());
			}

			auto groups = section->groups.createGroupMap();
			if(!section->defaultGroup.isNull())
				groups.append(QStringLiteral("."), section->defaultGroup);

			foreach(auto groupElement, groups) {
				const QSharedPointer<SettingsGroup> &group = groupElement.second;
				group->testNotLocked();

				if(group->entries.contains(id)) {
					return SettingsPathParser::createPath(categoryElement.first,
														  sectionElement.first,
														  groupElement.first);
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
		return this->getGroup(elements[2], elements[1], elements[0]);
	}
}
