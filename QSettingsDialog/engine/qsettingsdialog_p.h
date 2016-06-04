#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"
#include "containerelements.h"

class QSettingsDialogPrivate
{
public:
	static QSettingsDialogPrivate *getPrivateInstance(QSettingsDialog *dialog);

	friend class QSettingsDialog;
	QSettingsDialog *q_ptr;

	QSettingsDialogPrivate(QSettingsDialog *q_ptr);

	QSharedPointer<SettingsRoot> rootElement;

	QString categoryId;
	QString sectionId;
	QString groupId;

	int currentIndexMax;
	QHash<int, EntryElement> entryMap;

	QSharedPointer<SettingsCategory> getCategory(const QString &categoryId = QString());
	QSharedPointer<SettingsSection> getSection(const QString &sectionId = QString(),
											   const QString &categoryId = QString());
	QSharedPointer<SettingsGroup> getGroup(const QString &groupId = QString(),
										   const QString &sectionId = QString(),
										   const QString &categoryId = QString());

	QString findEntryPath(int id);
	QSharedPointer<SettingsGroup> findEntryGroup(int id);
};

#endif // QSETTINGSDIALOG_P_H
