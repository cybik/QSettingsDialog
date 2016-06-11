#include <QApplication>
#include <qsettingsdialog.h>
#include "testentry.h"
#include "delayedtestentry.h"

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

	// general test on typical appeareances of normal items
	dialog.setContainer("..");
	dialog.setSection("generalTest", "generalTest");
	dialog.appendEntry(new TestEntry(false, false));
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, false));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("normal", "normal");
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(false, true, "withFixedData"));
	dialog.appendEntry(new TestEntry(true, true));
	dialog.appendEntry(new TestEntry(true, true, "withOptionalData"));

	//checking test, does auto-checking work?
	dialog.setSection("checkingTest", "checkingTest");
	dialog.setGroup("optional1", "optional - no data", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional2", "optional - fixed data", true);
	dialog.appendEntry(new TestEntry(false, true, "fixed group data"));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional3", "optional - optional subdata", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true, "optional group data"));

	//custom group test
	dialog.setSection("customGroupsTest", "customGroupsTest");
	dialog.setGroup(".");
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(false, true));

	dialog.appendEntryAsGroup(new TestEntry(true, true, "LOOOOL"));
	dialog.setGroup("someGroup", "someGroup");
	dialog.appendEntryAsGroup(new TestEntry(false, false));
	dialog.appendEntryAsGroup(new TestEntry(false, true, QVariant(), false));
	dialog.appendEntryAsGroup(new TestEntry(false, false, QVariant(), false));

	//async test
	dialog.setSection("asyncTest", "asyncTest");
	dialog.setGroup(".");

	dialog.appendEntry(new DelayedTestEntry("test500", 500, qApp));
	dialog.appendEntry(new DelayedTestEntry("test1000", 1000, qApp));
	dialog.appendEntry(new DelayedTestEntry("test1500", 1500, qApp));

	dialog.showSettings();
	return a.exec();
}
