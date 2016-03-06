#include "qsettingsdialog.h"
#include "qsettingsdialog_p.h"

QSettingsDialog::QSettingsDialog(QObject *parent) :
	QObject(parent),
	d_ptr(new QSettingsDialogPrivate(this))
{

}

QSettingsDialog::~QSettingsDialog() {}

void QSettingsDialog::showDialog()
{
	Q_D(QSettingsDialog);
	d->mainDialg->open();
}



QSettingsDialogPrivate::QSettingsDialogPrivate(QSettingsDialog *q_ptr) :
	q_ptr(q_ptr),
	mainDialg(new DisplayDialog(Q_NULLPTR))
{

}
