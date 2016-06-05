#include "settingsdisplaydialog.h"
#include "ui_settingsdisplaydialog.h"
#include <dialogmaster.h>
#include <QTabWidget>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>

SettingsDisplayDialog::SettingsDisplayDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingsDisplayDialog),
	delegate(nullptr),
	maxWidthBase(0)
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);

	connect(this->ui->buttonBox, &QDialogButtonBox::clicked,
			this, &SettingsDisplayDialog::buttonBoxClicked);

	int listSpacing = this->style()->pixelMetric(QStyle::PM_LayoutVerticalSpacing);
	this->delegate = new CategoryItemDelegate(std::bind(&SettingsDisplayDialog::updateWidth, this, std::placeholders::_1),
											  this->ui->categoryListWidget->iconSize(),
											  qMax(qRound(listSpacing * (2./3.)), 1),
											  this);
	this->ui->categoryListWidget->setItemDelegate(this->delegate);
	this->ui->categoryListWidget->setSpacing(qMax(qRound(listSpacing / 3.), 1) - 1);

	int spacing = this->style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing);
	this->ui->contentLayout->setSpacing(spacing);
	this->ui->categoryLineSpacer->changeSize(spacing,
											 0,
											 QSizePolicy::Fixed,
											 QSizePolicy::Fixed);
}

SettingsDisplayDialog::~SettingsDisplayDialog()
{
	delete ui;
}

void SettingsDisplayDialog::createUi(const QSharedPointer<SettingsRoot> &elementRoot)
{
	if(elementRoot->defaultCategory)
		this->createCategory(elementRoot->defaultCategory);
	foreach(auto category, elementRoot->categories)
		this->createCategory(category.second);

	this->resetListSize();
	this->ui->categoryListWidget->setCurrentRow(0);
}

void SettingsDisplayDialog::resetListSize()
{
	int max = this->ui->categoryListWidget->count();
	if(max <= 1) {
		this->ui->categoryContentWidget->hide();
		this->resize(this->width() - this->ui->categoryContentWidget->sizeHint().width(),
					 this->height());
	} else {
		auto width = this->ui->categoryListWidget->sizeHint().width();
		this->ui->categoryListWidget->setFixedWidth(width);
		this->maxWidthBase = width;
	}
}

void SettingsDisplayDialog::updateWidth(int width)
{
	if(width > this->maxWidthBase) {
		this->maxWidthBase = width;
		QStyle *style = this->ui->categoryListWidget->style();
		width += style->pixelMetric(QStyle::PM_ScrollBarExtent);
		width += style->pixelMetric(QStyle::PM_LayoutHorizontalSpacing);
		this->ui->categoryListWidget->setFixedWidth(width);
	}
}

void SettingsDisplayDialog::buttonBoxClicked(QAbstractButton *button)
{
	switch(this->ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::Ok:
		emit save(true);
		//DEBUG
		this->accept();
		break;
	case QDialogButtonBox::Cancel:
		this->reject();
		break;
	case QDialogButtonBox::Apply:
		emit save(false);
		break;
	case QDialogButtonBox::RestoreDefaults:
		if(DialogMaster::warning(this,
								 tr("All custom changes will be deleted and the defaults restored. "
									"<i>This cannot be undone!</i>"),
								 tr("%1?").arg(button->text()),
								 QString(),
								 QMessageBox::Yes | QMessageBox::No,
								 QMessageBox::Yes,
								 QMessageBox::No)
		   == QMessageBox::Yes) {
			emit reset();
			//DEBUG
			this->accept();
		}
		break;
	default:
		Q_UNREACHABLE();
	}
}

void SettingsDisplayDialog::createCategory(const QSharedPointer<SettingsCategory> &category)
{
	auto item = new QListWidgetItem();
	item->setText(category->name);
	item->setIcon(category->icon);
	item->setToolTip(category->tooltip.isNull() ? category->name : category->tooltip);
	auto tab = new QTabWidget();
	tab->setTabBarAutoHide(true);

	this->ui->contentStackWidget->addWidget(tab);
	this->ui->categoryListWidget->addItem(item);

	if(category->defaultSection)
		this->createSection(category->defaultSection, tab);
	foreach(auto section, category->sections)
		this->createSection(section.second, tab);
}

void SettingsDisplayDialog::createSection(const QSharedPointer<SettingsSection> &section, QTabWidget *tabWidget)
{
	auto scrollArea = new QScrollArea();
	scrollArea->setWidgetResizable(true);
	scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setAutoFillBackground(true);
	auto pal = scrollArea->palette();
	pal.setColor(QPalette::Window, Qt::transparent);
	scrollArea->setPalette(pal);
	scrollArea->setFrameShape(QFrame::NoFrame);

	auto scrollContent = new QWidget(scrollArea);
	auto layout = new QVBoxLayout(scrollContent);
	scrollContent->setLayout(layout);
	scrollArea->setWidget(scrollContent);

	auto index = tabWidget->addTab(scrollArea, section->icon, section->name);
	tabWidget->tabBar()->setTabToolTip(index, section->tooltip.isNull() ? section->name : section->tooltip);

	if(section->defaultGroup)
		this->createDefaultGroup(section->defaultGroup, scrollContent);
	foreach(auto group, section->groups)
		this->createGroup(group.second, scrollContent);

	layout->addStretch();
}

void SettingsDisplayDialog::createDefaultGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget)
{
	auto defaultWidget = new QWidget(contentWidget);
	defaultWidget->setToolTip(group->tooltip.isNull() ? group->name : group->tooltip);
	auto layout = new QFormLayout(defaultWidget);
	layout->setContentsMargins(QMargins());
	defaultWidget->setLayout(layout);
	contentWidget->layout()->addWidget(defaultWidget);

	foreach(auto entry, group->entries)
		this->createEntry(entry.second, defaultWidget);
}

void SettingsDisplayDialog::createGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget)
{
	auto box = new QGroupBox(group->name, contentWidget);
	box->setToolTip(group->tooltip.isNull() ? group->name : group->tooltip);
	if(group->isOptional) {
		box->setCheckable(true);
		box->setChecked(false);
	}
	box->setLayout(new QFormLayout(box));
	contentWidget->layout()->addWidget(box);

	foreach(auto entry, group->entries)
		this->createEntry(entry.second, box);
}

void SettingsDisplayDialog::createEntry(const QSharedPointer<QSettingsEntry> &entry, QWidget *groupWidget)
{
	QWidget *content = nullptr;
	auto settingsWidget = entry->createWidget(groupWidget);
	if(settingsWidget)
		content = settingsWidget->asWidget();
	else {
		content = new QWidget(groupWidget);
		auto layout = new QHBoxLayout(content);
		layout->setContentsMargins(QMargins());
		content->setLayout(layout);

		auto iconLabel = new QLabel(content);
		iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(16, 16));
		layout->addWidget(iconLabel);
		layout->setStretchFactor(iconLabel, 0);

		auto errorTextLabel = new QLabel(tr("<i>Failed to load element</i>"), content);
		errorTextLabel->setEnabled(false);
		layout->addWidget(errorTextLabel);
		layout->setStretchFactor(errorTextLabel, 1);
	}

	Q_ASSERT(dynamic_cast<QFormLayout*>(groupWidget->layout()));
	auto layout = static_cast<QFormLayout*>(groupWidget->layout());
	if(entry->isOptional()) {
		content->setEnabled(false);
		auto optBox = new QCheckBox(entry->entryName() + tr(":"), groupWidget);
		QObject::connect(optBox, &QCheckBox::toggled,
						 content, &QWidget::setEnabled);
		layout->addRow(optBox, content);
	} else
		layout->addRow(entry->entryName() + tr(":"), content);

	//TODO tell engine the widget and the loader
}



CategoryItemDelegate::CategoryItemDelegate(std::function<void (int)> updateFunc, const QSize &iconSize, int layoutSpacing, QObject *parent) :
	QStyledItemDelegate(parent),
	iconSize(),
	updateFunc(updateFunc)
{
	this->iconSize = iconSize + QSize(0, layoutSpacing);
}

QSize CategoryItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize size = this->QStyledItemDelegate::sizeHint(option, index);
	this->updateFunc(size.width());
	return size.expandedTo(this->iconSize);
}
