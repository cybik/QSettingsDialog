#ifndef SETTINGSDISPLAYDIALOG_H
#define SETTINGSDISPLAYDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QAbstractButton>
#include <QProgressDialog>
#include <functional>
#include "containerelements.h"
#include "checkinghelper.h"
class SettingsEngine;

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
	explicit SettingsDisplayDialog(SettingsEngine *engine, QWidget *parent = 0);
	~SettingsDisplayDialog();

	void createUi(const QSharedPointer<SettingsRoot> &elementRoot);

public slots:
	int exec() override;

signals:
	void reset();

private slots:
	void startSaving(bool isApply);

	void loadFinished(int errorCount);
	void saveFinished(int errorCount);
	void completeAbort();

	void resetListSize();
	void updateWidth(int width);

	void buttonBoxClicked(QAbstractButton *button);

private:
	enum OperationMode {
		Idle,
		Load,
		Save,
		Apply,
		Reset
	};

	SettingsEngine *engine;

	Ui::SettingsDisplayDialog *ui;	
	CategoryItemDelegate *delegate;
	int maxWidthBase;

	OperationMode currentMode;
	QProgressDialog *workingDialog;

	void createCategory(const QSharedPointer<SettingsCategory> &category);
	void createSection(const QSharedPointer<SettingsSection> &section, QTabWidget *tabWidget);
	void createDefaultGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget);
	void createGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget);
	void createCustomGroup(const QSharedPointer<QSettingsEntry> &group, QWidget *contentWidget);
	void createEntry(const QSharedPointer<QSettingsEntry> &entry, QWidget *groupWidget, CheckingHelper *helper);

	QWidget *createErrorWidget(QWidget *parent);
};

#endif // SETTINGSDISPLAYDIALOG_H
