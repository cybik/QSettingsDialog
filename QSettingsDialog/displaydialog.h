#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QListWidget>
#include <QTableWidget>

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

	void insertItem(int index, QListWidgetItem *item, QTabWidget *content);
	void deleteItem(int index);
	void moveItem(int from, int to);

	QSize iconSize() const;
	void updateIconSize(const QSize &size);

protected:
	void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private slots:
	void resetListSize();
	void updateWidth(int width);

	void on_buttonBox_clicked(QAbstractButton *button);

private:
	Ui::DisplayDialog *ui;
	CategoryItemDelegate *delegate;
	int maxWidthBase;
};

#endif // DISPLAYDIALOG_H
