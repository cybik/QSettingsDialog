#include <QApplication>
#include <qsettingsdialog.h>
#include <qsettingswidgetdialogengine.h>
#include <qsettingspropertyentry.h>
#include <qsettingssettingsloader.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setApplicationName("appname");

	QSettingsDialog dialog;

	QObject::connect(&dialog, &QSettingsDialog::saved, [](bool close) {
		qDebug() << "---- Save completed" << (close ? "with" : "without") << "closing ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::resetted, []() {
		qDebug() << "---- Reset completed ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::canceled, []() {
		qDebug() << "---- Dialog was canceled ----";
	});

	QObject::connect(qApp, &QApplication::applicationNameChanged, []() {
		qDebug() << "Name was changed!!! To" << QApplication::applicationName();
	});

	dialog.appendEntry(new QSettingsPropertyEntry("applicationName", qApp, "property"));

	QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);
	dialog.appendEntry(new QSettingsEntry(QMetaType::QDateTime,
										  new QSettingsSettingsLoader(&settings, "datetime"),
										  "settings.ini"));

	dialog.openSettings();
	return a.exec();
}
