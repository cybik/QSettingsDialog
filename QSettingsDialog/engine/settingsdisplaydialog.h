#ifndef SETTINGSDISPLAYDIALOG_H
#define SETTINGSDISPLAYDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QAbstractButton>
#include <functional>
#include "containerelements.h"

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
	std::function<void(int)> updateFunc;
};

class SettingsDisplayDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDisplayDialog(QWidget *parent = 0);
	~SettingsDisplayDialog();

	void createUi(const QSharedPointer<SettingsRoot> &elementRoot);

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

	void createCategory(const QSharedPointer<SettingsCategory> &category);
	void createSection(const QSharedPointer<SettingsSection> &section, QTabWidget *tabWidget);
	void createDefaultGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget);
	void createGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget);
	void createEntry(const QSharedPointer<QSettingsEntry> &entry, QWidget *groupWidget);
};

#endif // SETTINGSDISPLAYDIALOG_H
