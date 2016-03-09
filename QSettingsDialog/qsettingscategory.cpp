#include "qsettingscategory.h"
#include <QListWidgetItem>
#include <QTabWidget>
#include <QScrollArea>
#include "qsettingssection.h"
#include "qsettingsdialog.h"

#define TEST_DEFAULT(index) (this->defaultSect ? (index + 1) : (index))

QSettingsCategory::QSettingsCategory(QListWidgetItem *listEntry, bool hasTooltip, QTabWidget *contentWidget) :
	listEntry(listEntry),
	hasTooltip(hasTooltip),
	contentWidget(contentWidget),
	defaultSect(Q_NULLPTR),
	sects()
{}

QSettingsCategory::~QSettingsCategory()
{
	delete this->defaultSect;
	foreach(QSettingsSection *section, this->sects)
		delete section;
}

QString QSettingsCategory::name() const
{
	return this->listEntry->text();
}

QIcon QSettingsCategory::icon() const
{
	return this->listEntry->icon();
}

QString QSettingsCategory::toolTip() const
{
	return this->listEntry->toolTip();
}

void QSettingsCategory::setName(const QString &name)
{
	this->listEntry->setText(name);
	if(!this->hasTooltip)
		this->listEntry->setToolTip(name);
}

void QSettingsCategory::setIcon(const QIcon &icon)
{
	this->listEntry->setIcon(icon);
}

void QSettingsCategory::setToolTip(const QString &toolTip)
{
	this->listEntry->setToolTip(toolTip);
	this->hasTooltip = !toolTip.isNull();
}

QList<QSettingsSection *> QSettingsCategory::sections(bool includeDefault) const
{
	QList<QSettingsSection *> sections = this->sects;
	if(includeDefault && this->defaultSect)
		sections.prepend(this->defaultSect);
	return sections;
}

int QSettingsCategory::sectionCount() const
{
	return this->sects.size();
}

QSettingsSection *QSettingsCategory::sectionAt(int index) const
{
	Q_ASSERT_X2(index >= 0 && index < this->sects.size(), "index out of range");
	return this->sects.at(index);
}

int QSettingsCategory::sectionIndex(QSettingsSection *section) const
{
	return this->sects.indexOf(section);
}

QSettingsSection *QSettingsCategory::insertSection(int index, const QString &name, const QIcon &icon)
{
	Q_ASSERT_X2(index >= 0 && index <= this->sects.size(), "index out of range");
	QSettingsSection *section = this->createSection(TEST_DEFAULT(index), name, icon);
	this->sects.insert(index, section);
	this->updateSectIndexes();

	return section;
}

void QSettingsCategory::deleteSection(int index)
{
	Q_ASSERT_X2(index >= 0 && index < this->sects.size(), "index out of range");
	QWidget *content = this->contentWidget->widget(TEST_DEFAULT(index));
	this->contentWidget->removeTab(TEST_DEFAULT(index));
	content->deleteLater();
	delete this->sects.takeAt(index);
	this->updateSectIndexes();
}

bool QSettingsCategory::deleteSection(QSettingsSection *section)
{
	int index = this->sects.indexOf(section);
	if(index >= 0) {
		this->deleteSection(index);
		return true;
	} else
		return false;
}

void QSettingsCategory::moveSection(int from, int to)
{
	Q_ASSERT_X2(from >= 0 && from < this->sects.size(), "index out of range");
	Q_ASSERT_X2(to >= 0 && to < this->sects.size(), "index out of range");
	this->contentWidget->tabBar()->moveTab(TEST_DEFAULT(from), TEST_DEFAULT(to));
	this->sects.move(from, to);
	this->updateSectIndexes();
}

QSettingsSection *QSettingsCategory::defaultSection()
{
	if(!this->defaultSect) {
		this->defaultSect = this->createSection(0, QSettingsDialog::tr("General"), QIcon());
		this->updateSectIndexes();
	}
	return this->defaultSect;
}

QSettingsGroup *QSettingsCategory::defaultGroup()
{
	return this->defaultSection()->defaultGroup();
}

bool QSettingsCategory::hasDefaultSection() const
{
	return this->defaultSect;
}

void QSettingsCategory::updateSectIndexes()
{
	for(int i = 0, max = this->sects.size(); i < max; ++i)
		this->sects[i]->updateIndex(TEST_DEFAULT(i));
}

QSettingsSection *QSettingsCategory::createSection(int index, const QString &name, const QIcon &icon)
{
	QScrollArea *scrollArea = new QScrollArea();
	scrollArea->setWidgetResizable(true);
	scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setAutoFillBackground(true);
	QPalette pal = scrollArea->palette();
	pal.setColor(QPalette::Window, Qt::transparent);
	scrollArea->setPalette(pal);
	scrollArea->setFrameShape(QFrame::NoFrame);

	QWidget *scrollContent = new QWidget();
	scrollArea->setWidget(scrollContent);

	this->contentWidget->insertTab(index, scrollArea, icon, name);
	return new QSettingsSection(this->contentWidget->tabBar(), index, scrollContent);
}
