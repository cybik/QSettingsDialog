#include <QApplication>
#include <qsettingsdialog.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;
	QObject::connect(&dialog, &QSettingsDialog::resetted,
					 qApp, &QApplication::quit,
					 Qt::QueuedConnection);

	dialog.showSettings();
	return a.exec();
}
