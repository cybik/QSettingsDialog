#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"
#include "containerelements.h"
#include "settingsengine.h"
#include "settingsdisplaydialog.h"
#include <QAtomicInt>
#include <QPointer>

class QSettingsDialogPrivate
{	
private:
	friend class QSettingsDialog;
	QSettingsDialogPrivate(QSettingsDialog *q_ptr);
	QAtomicInt currentIdMax;

public:
	static QSettingsDialogPrivate *getPrivateInstance(QSettingsDialog *dialog);

	QSettingsDialog *q_ptr;

	QSharedPointer<SettingsRoot> rootElement;

	QString categoryId;
	QString sectionId;
	QString groupId;

	QPointer<SettingsDisplayDialog> currentDialog;

	int getNextId();

	QSharedPointer<SettingsCategory> getCategory(QString categoryId = QString());
	QSharedPointer<SettingsSection> getSection(QString sectionId = QString(),
											   const QString &categoryId = QString());
	QSharedPointer<SettingsGroup> getGroup(QString groupId = QString(),
										   const QString &sectionId = QString(),
										   const QString &categoryId = QString());

	QString findEntryPath(int id);
	QSharedPointer<SettingsGroup> findEntryGroup(int id);

	int showDialog(bool asExec, QWidget *parentWindow);
};

#endif // QSETTINGSDIALOG_P_H
