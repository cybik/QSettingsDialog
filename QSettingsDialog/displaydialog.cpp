#include "displaydialog.h"
#include "ui_displaydialog.h"
#include <QStyledItemDelegate>
#include <dialogmaster.h>

class CategoryItemDelegate : public QStyledItemDelegate
{
public:
	CategoryItemDelegate(QObject *parent = Q_NULLPTR);

	void setIconSize(const QSize &size);

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
	QSize extendSize;
};

DisplayDialog::DisplayDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DisplayDialog),
	delegate(new CategoryItemDelegate(this))
{
	ui->setupUi(this);
	DialogMaster::masterDialog(this);
	this->delegate->setIconSize(this->ui->categoryListWidget->iconSize());
	this->ui->categoryListWidget->setItemDelegate(this->delegate);
	this->ui->categoryLineSpacer->changeSize(this->style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing),
											 0,
											 QSizePolicy::Fixed,
											 QSizePolicy::Fixed);

	connect(this->ui->categoryListWidget, &QListWidget::iconSizeChanged,
			this->delegate, &CategoryItemDelegate::setIconSize);

	this->updateListItems();
}

DisplayDialog::~DisplayDialog()
{
	delete ui;
}

void DisplayDialog::updateListItems()
{
	int max = this->ui->categoryListWidget->count();
	if(max == 0) {
		this->ui->categoryContentWidget->hide();
	} else {
		this->ui->categoryContentWidget->show();

		int width = this->ui->categoryListWidget->sizeHint().width();
		for(int i = 0; i < max; ++i)
			width = qMax(width, this->ui->categoryListWidget->item(i)->sizeHint().width());
		width += this->ui->categoryListWidget->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
		this->ui->categoryListWidget->setFixedWidth(width);
		this->ui->categoryListWidget->show();
		this->ui->listSeperatorLine->show();
	}
}

void DisplayDialog::on_buttonBox_clicked(QAbstractButton *button)
{
	switch(this->ui->buttonBox->standardButton(button)) {
	case QDialogButtonBox::Ok:
		this->accept();
		break;
	case QDialogButtonBox::Cancel:
		this->reject();
		break;
	case QDialogButtonBox::Apply:
		break;
	case QDialogButtonBox::RestoreDefaults:
		if(DialogMaster::warning(this,
								 tr("All custom changes will be delete and the defaults restored. "
									"This cannot be undone."),
								 tr("%1?").arg(button->text()),
								 QString(),
								 QMessageBox::Yes,
								 QMessageBox::No)
		   == QMessageBox::Yes) {
			this->done(2);
		}
		break;
	default:
		Q_UNREACHABLE();
	}
}



CategoryItemDelegate::CategoryItemDelegate(QObject *parent) :
	QStyledItemDelegate(parent),
	extendSize()
{}

void CategoryItemDelegate::setIconSize(const QSize &size)
{
	this->extendSize = size;
}

QSize CategoryItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSize size = this->QStyledItemDelegate::sizeHint(option, index);
	return size.expandedTo(this->extendSize);
}
