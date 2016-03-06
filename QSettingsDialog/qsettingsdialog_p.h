#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"
#include "displaydialog.h"
#include "qsettingscategory.h"

class QSettingsDialogPrivate
{
public:
	static QSettingsDialogPrivate *getPrivate(QSettingsDialog *dialog);

private:
	QSettingsDialog *q_ptr;
	Q_DECLARE_PUBLIC(QSettingsDialog)

	QSettingsDialogPrivate(QSettingsDialog *q_ptr);

	DisplayDialog *mainDialg;
	QSettingsCategory *defaultCategory;
	QList<QSettingsCategory*> categories;
};

#define SPRIV(dialog) QSettingsDialogPrivate::getPrivate(dialog)

#endif // QSETTINGSDIALOG_P_H
