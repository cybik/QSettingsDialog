#ifndef QSETTINGSDIALOG_H
#define QSETTINGSDIALOG_H

#include "qsettingsdialog_global.h"
#include <QObject>
#include <QScopedPointer>

class QSettingsDialogPrivate;
class QSETTINGSDIALOGSHARED_EXPORT QSettingsDialog : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(QSettingsDialog)

public:
	QSettingsDialog(QObject *parent = Q_NULLPTR);
	~QSettingsDialog();

	void showDialog();

private:
	QScopedPointer<QSettingsDialogPrivate> d_ptr;
	Q_DECLARE_PRIVATE(QSettingsDialog)
};

#endif // QSETTINGSDIALOG_H
