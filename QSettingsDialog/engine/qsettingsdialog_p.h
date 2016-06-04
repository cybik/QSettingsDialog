#ifndef QSETTINGSDIALOG_P_H
#define QSETTINGSDIALOG_P_H

#include "qsettingsdialog.h"

class QSettingsDialogPrivate
{
public:
	static QSettingsDialogPrivate *getPrivateInstance(QSettingsDialog *dialog);

	friend class QSettingsDialog;
	QSettingsDialog *q_ptr;

	QSettingsDialogPrivate(QSettingsDialog *q_ptr);
};

#endif // QSETTINGSDIALOG_P_H
