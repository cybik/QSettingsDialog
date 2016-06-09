#include <QApplication>
#include <qsettingsdialog.h>
#include "testentry.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;
	QObject::connect(&dialog, &QSettingsDialog::resetted,
					 qApp, &QApplication::quit,
					 Qt::QueuedConnection);

	//container demo
	dialog.setCategory("baum", "Baum == 42");
	dialog.setSection(".");
	dialog.setSection("__", "Is it true?", QIcon(), "some tooltop");

	dialog.setGroup(".");
	dialog.appendEntry(new TestEntry(false, true, "moreText"));

	dialog.setGroup("42", "Yes it is!", true, "Even here...");
	dialog.appendEntry(new TestEntry(false, false));
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, false));
	dialog.appendEntry(new TestEntry(true, true));

	// settings widget optional handling
	dialog.setContainer("..");
	dialog.appendEntry(new TestEntry(false, false));
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, false));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("normal", "normal");
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(false, true, "withFixedData"));
	dialog.appendEntry(new TestEntry(true, true));
	dialog.appendEntry(new TestEntry(true, true, "withOptionalData"));

	dialog.appendEntryAsGroup(new TestEntry(true, true, "LOOOOL"));

	dialog.setGroup("optional1", "optional - no data", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional2", "optional - fixed data", true);
	dialog.appendEntry(new TestEntry(false, true, "fixed group data"));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional3", "optional - optional subdata", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true, "optional group data"));

	dialog.appendEntryAsGroup(new TestEntry(false, false));
	dialog.appendEntryAsGroup(new TestEntry(false, true, QVariant(), false));
	dialog.appendEntryAsGroup(new TestEntry(false, false, QVariant(), false));


	dialog.showSettings();
	return a.exec();
}
