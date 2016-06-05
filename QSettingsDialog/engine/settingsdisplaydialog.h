#ifndef SETTINGSDISPLAYDIALOG_H
#define SETTINGSDISPLAYDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QAbstractButton>
#include <functional>

namespace Ui {
	class SettingsDisplayDialog;
}

class CategoryItemDelegate : public QStyledItemDelegate
{
public:
	CategoryItemDelegate(std::function<void(int)> updateFunc,
						 const QSize &iconSize,
						 int layoutSpacing,
						 QObject *parent = Q_NULLPTR);

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
	QSize iconSize;
	std::function<void(int)> updateFunc;//TODO use signal/slot instead!
};

class SettingsDisplayDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDisplayDialog(QWidget *parent = 0);
	~SettingsDisplayDialog();

signals:
	void save(bool quitAfter);
	void reset();

private slots:
	void resetListSize();
	void updateWidth(int width);

	void buttonBoxClicked(QAbstractButton *button);

private:
	Ui::SettingsDisplayDialog *ui;	
	CategoryItemDelegate *delegate;
	int maxWidthBase;
};

#endif // SETTINGSDISPLAYDIALOG_H
