#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"
#include "qsettingscategory.h"
#include "qsettingsgroup.h"
#include "qsettingsentry.h"
#include <QScopedPointer>
#include <QHash>
#include <QProgressDialog>
#include <QSignalMapper>
#include <QStyledItemDelegate>
#include <functional>
class QAbstractButton;

namespace Ui {
	class QSettingsDialog;
}

class CategoryItemDelegate : public QStyledItemDelegate
{
public:
	CategoryItemDelegate(std::function<void(int)> updateFunc, int layoutSpacing, QObject *parent = Q_NULLPTR);

	void setIconSize(const QSize &size);

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
	int spacing;
	QSize extendSize;
	std::function<void(int)> updateFunc;//TODO use signal/slot instead!
};

class QSettingsDialogPrivate : public QObject
{
public:
	~QSettingsDialogPrivate();

	void addSettingsEntry(QSettingsEntry *entry, QSettingsWidgetBase *widget);
	void removeSettingsEntry(QSettingsEntry *entry);

	void startSaving(bool closeDown);
	void discard();
	void reset();

private slots:
	void loadDone(const QVariant &data, bool isUser);
	void saveDone(bool successfull);
	void resetDone(bool successfull);
	void progressCanceled();

	void resetListSize();
	void updateWidth(int width);

	void buttonBoxClicked(QAbstractButton *button);

private:
	typedef QHash<QSettingsLoader*, QSettingsWidgetBase*>::const_iterator const_iter;

	QSettingsDialog *q_ptr;
	Q_DECLARE_PUBLIC(QSettingsDialog)

	QSettingsDialogPrivate(QSettingsDialog *q_ptr);

	QSettingsCategory *createCategory(int index, const QString &name, const QIcon &icon, const QString &toolTip = QString());

	void startLoading();

	void setEditable(bool editable);

	QSettingsCategory *defaultCategory;
	QList<QSettingsCategory*> categories;

	Ui::QSettingsDialog *ui;
	CategoryItemDelegate *delegate;
	int maxWidthBase;

	QProgressDialog *progressDialog;
	int currentValue;
	bool closeDown;

	QHash<QSettingsLoader*, QSettingsWidgetBase*> entryMap;
};

#endif // QSETTINGSDIALOG_P_H
