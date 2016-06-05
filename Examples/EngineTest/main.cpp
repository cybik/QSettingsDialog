#include <QApplication>
#include <qsettingsdialog.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;
	QObject::connect(&dialog, &QSettingsDialog::resetted,
					 qApp, &QApplication::quit,
					 Qt::QueuedConnection);

	dialog.setGroup(".");
	dialog.setCategory("baum", "Baum == 42");
	dialog.setSection(".");
	dialog.setSection("__", "Is it true?", QIcon(), "some tooltop");
	dialog.setGroup(".");
	dialog.setGroup("42", "Yes it is!", true, "Even here...");

	dialog.showSettings();
	return a.exec();
}
