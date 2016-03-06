#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
	class DisplayDialog;
}
class CategoryItemDelegate;

class DisplayDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DisplayDialog(QWidget *parent = 0);
	~DisplayDialog();

private slots:
	void updateListItems();

	void on_buttonBox_clicked(QAbstractButton *button);

private:
	Ui::DisplayDialog *ui;
	CategoryItemDelegate *delegate;
};

#endif // DISPLAYDIALOG_H
