#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"
#include "displaydialog.h"
#include "qsettingscategory.h"
#include "qsettingsentry.h"
#include <QScopedPointer>
#include <QHash>
#include <QProgressDialog>
#include <QSignalMapper>

class QSettingsDialogPrivate
{
public:
	~QSettingsDialogPrivate();

	void addSettingsEntry(QSettingsEntry *entry, QSettingsWidgetBase *widget);
	void removeSettingsEntry(QSettingsEntry *entry);

	void startSaving(bool closeDown);
	void discard();
	void reset();

private:
	typedef QHash<QSettingsLoader*, QSettingsWidgetBase*>::const_iterator const_iter;

	QSettingsDialog *q_ptr;
	Q_DECLARE_PUBLIC(QSettingsDialog)

	QSettingsDialogPrivate(QSettingsDialog *q_ptr);

	QSettingsCategory *createCategory(int index, const QString &name, const QIcon &icon, const QString &toolTip = QString());

	void startLoading();

	DisplayDialog *mainDialog;
	QSettingsCategory *defaultCategory;
	QList<QSettingsCategory*> categories;

	QProgressDialog *progressDialog;
	int currentMax;
	bool closeDown;

	QHash<QSettingsLoader*, QSettingsWidgetBase*> entryMap;
};

#endif // QSETTINGSDIALOG_P_H
