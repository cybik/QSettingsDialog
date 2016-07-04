#include <QApplication>
#include <qsettingsdialog.h>
#include <qsettingssettingsloader.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettings settings(QApplication::applicationDirPath() + "/test.ini", QSettings::IniFormat);

	//a simple example showing how to display values from settings with the dialog
	QSettingsDialog dialog;
	dialog.appendEntry(new QSettingsEntry(QMetaType::QString,
										  new QSettingsSettingsLoader(&settings, "appName"),
										  "App name"));
	dialog.appendEntry(new QSettingsEntry(QMetaType::QString,
										  new QSettingsSettingsLoader(&settings, "companyName"),
										  "Company name"));

	dialog.setGroup("versionGroup", 0, "Version", true, "Please configure the version");
	dialog.appendEntry(new QSettingsEntry(QMetaType::Int,
										  new QSettingsSettingsLoader(&settings, "version/major"),
										  "Major",
										  false,
										  QString(),
										  {{"minimum", 0}, {"maximum", 9}}));
	dialog.appendEntry(new QSettingsEntry(QMetaType::Int,
										  new QSettingsSettingsLoader(&settings, "version/minor"),
										  "Minor",
										  false,
										  QString(),
										  {{"minimum", 0}, {"maximum", 9}}));
	dialog.appendEntry(new QSettingsEntry(QMetaType::Int,
										  new QSettingsSettingsLoader(&settings, "version/patch"),
										  "Patch",
										  false,
										  QString(),
										  {{"minimum", 0}, {"maximum", 9}}));

	dialog.unsetGroup();
	dialog.appendEntry(new QSettingsEntry(QMetaType::QString,
										  new QSettingsSettingsLoader(&settings, "authorName"),
										  "Load Programmer",
										  true));

	dialog.setSection("more", "More Stuff");
	dialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
										  new QSettingsSettingsLoader(&settings, "allow/A"),
										  "Allow Option A"));
	dialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
										  new QSettingsSettingsLoader(&settings, "allow/B"),
										  "Allow Option B"));
	dialog.appendEntry(new QSettingsEntry(QMetaType::Bool,
										  new QSettingsSettingsLoader(&settings, "allow/C"),
										  "Allow Option C"));

	dialog.setCategory("secret", "Secret Secure Settings", QIcon(":/QSettingsDialog/icons/gearSettings.ico"));
	dialog.setSection(".");//will not be required in next version
	dialog.appendEntry(new QSettingsEntry(QMetaType::QUrl,
										  new QSettingsSettingsLoader(&settings, "secretUrl"),
										  "Very secret url"));
	dialog.appendEntry(new QSettingsEntry(QMetaType::QColor,
										  new QSettingsSettingsLoader(&settings, "secretColor"),
										  "Very secret color"));

	return dialog.execSettings();
}
