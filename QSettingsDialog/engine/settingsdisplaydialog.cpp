#include "settingsdisplaydialog.h"
#include "ui_settingsdisplaydialog.h"
#include <dialogmaster.h>
#include <QTabWidget>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include "settingsengine.h"

SettingsDisplayDialog::SettingsDisplayDialog(SettingsEngine *engine, QWidget *parent) :
	QDialog(parent),
	engine(engine),
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

	//engine
	connect(this->engine, &SettingsEngine::loadCompleted,
			this, &SettingsDisplayDialog::loadFinished);
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

int SettingsDisplayDialog::exec()
{
	this->workingDialog = DialogMaster::createProgress(this, tr("Loading settings…"));
	this->workingDialog->setAutoClose(false);
	this->workingDialog->setAutoReset(false);
	//TODO handle cancel
	connect(this->engine, &SettingsEngine::progressMaxChanged,
			this->workingDialog, &QProgressDialog::setMaximum);
	connect(this->engine, &SettingsEngine::progressValueChanged,
			this->workingDialog, &QProgressDialog::setValue);

	this->setContentEnabled(false);
	this->engine->startLoading();
	return this->QDialog::exec();
}

void SettingsDisplayDialog::loadFinished()
{
	if(this->workingDialog) {
		this->workingDialog->close();
		this->workingDialog->deleteLater();
		this->workingDialog = nullptr;
	}
	this->setContentEnabled(true);
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
	foreach(auto group, section->groups) {
		if(group.first.type() == QMetaType::Int)
			this->createCustomGroup(group.second.second, scrollContent);
		else
			this->createGroup(group.second.first, scrollContent);
	}

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
		this->createEntry(entry.second, defaultWidget, nullptr);
}

void SettingsDisplayDialog::createGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget)
{
	auto box = new CheckingGroupBox(contentWidget);
	box->setTitle(group->name);
	box->setToolTip(group->tooltip.isNull() ? group->name : group->tooltip);
	if(group->isOptional) {
		box->setCheckable(true);
		box->setChecked(false);
	}
	box->setLayout(new QFormLayout(box));
	contentWidget->layout()->addWidget(box);

	foreach(auto entry, group->entries)
		this->createEntry(entry.second, box, group->isOptional ? box : nullptr);
}

void SettingsDisplayDialog::createCustomGroup(const QSharedPointer<QSettingsEntry> &group, QWidget *contentWidget)
{
	auto rContainer = contentWidget;
	CheckingHelper *helper = nullptr;

	if(!group->entryName().isNull() ||
	   group->isOptional()) {
		auto box = new CheckingGroupBox(contentWidget);
		box->setTitle(group->entryName());
		auto ttip = group->tooltip();
		box->setToolTip(ttip.isNull() ? group->entryName() : ttip);

		if(group->isOptional()) {
			box->setCheckable(true);
			box->setChecked(false);
			helper = box;
		}

		box->setLayout(new QVBoxLayout(box));
		contentWidget->layout()->addWidget(box);
		rContainer = box;
	}

	QWidget *content = nullptr;
	auto settingsWidget = group->createWidget(rContainer);
	if(settingsWidget)
		content = settingsWidget->asWidget();
	else
		content = this->createErrorWidget(rContainer);
	rContainer->layout()->addWidget(content);

	if(settingsWidget)
		this->engine->addEntry(group, settingsWidget, helper);
}

void SettingsDisplayDialog::createEntry(const QSharedPointer<QSettingsEntry> &entry, QWidget *groupWidget, CheckingHelper *helper)
{
	QWidget *content = nullptr;
	auto settingsWidget = entry->createWidget(groupWidget);
	if(settingsWidget)
		content = settingsWidget->asWidget();
	else
		content = this->createErrorWidget(groupWidget);

	Q_ASSERT(dynamic_cast<QFormLayout*>(groupWidget->layout()));
	auto layout = static_cast<QFormLayout*>(groupWidget->layout());
	QWidget *label = nullptr;
	CheckingHelper *labelAsHelper = nullptr;
	if(entry->isOptional()) {
		auto optBox = new CheckingCheckBox(groupWidget, helper);
		optBox->setText(entry->entryName() + tr(":"));
		QObject::connect(optBox, &QCheckBox::toggled,
						 content, &QWidget::setEnabled);
		label = optBox;
		labelAsHelper = optBox;
	} else {
		auto cLabel = new CheckingLabel(groupWidget, helper);
		cLabel->setText(entry->entryName() + tr(":"));
		label = cLabel;
		labelAsHelper = cLabel;
	}

	label->setToolTip(entry->tooltip());
	if(content->toolTip().isNull())
		content->setToolTip(entry->tooltip());
	if(!settingsWidget)
		label->setEnabled(false);
	else
		content->setEnabled(!entry->isOptional());
	layout->addRow(label, content);

	if(settingsWidget)
		this->engine->addEntry(entry, settingsWidget, labelAsHelper);
}

QWidget *SettingsDisplayDialog::createErrorWidget(QWidget *parent)
{
	auto content = new QWidget(parent);
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

	return content;
}

void SettingsDisplayDialog::setContentEnabled(bool enabled)
{
	this->ui->contentStackWidget->setEnabled(enabled);
	this->ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
	this->ui->buttonBox->button(QDialogButtonBox::Apply)->setEnabled(enabled);
	this->ui->buttonBox->button(QDialogButtonBox::RestoreDefaults)->setEnabled(enabled);
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
