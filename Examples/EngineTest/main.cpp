#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <qsettingsdialog.h>
#include <qsettingscontainer.h>
#include <qsettingslayout.h>
#include "testentry.h"
#include "delayedtestentry.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;
	QObject::connect(&dialog, &QSettingsDialog::resetted,
					 qApp, &QApplication::quit,
					 Qt::QueuedConnection);

	QObject::connect(&dialog, &QSettingsDialog::saved, [](bool close) {
		qDebug() << "---- Save completed" << (close ? "with" : "without") << "closing ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::resetted, []() {
		qDebug() << "---- Reset completed ----";
	});
	QObject::connect(&dialog, &QSettingsDialog::canceled, []() {
		qDebug() << "---- Dialog was canceled ----";
	});

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

	//container test
	dialog.setContainer("containerTest/b/normal");
	dialog.appendEntry(new TestEntry(false, true));

	QSettingsContainer container(&dialog, "containerTest/b/normal");
	container.appendEntry(new TestEntry(true, true));
	auto rem = dialog.appendEntry(new TestEntry(false, true));
	container.insertEntry(1, new TestEntry(false, false));

	QSettingsContainer container2(&dialog, "containerTest/b/normal");
	container2.removeEntry(rem);
	dialog.prependEntry(new TestEntry(false, true));

	//async container test
	QAsyncSettingsContainer asyncContainer(&dialog, "containerTest/b/async");
	asyncContainer.appendEntry(new TestEntry(false, false));
	dialog.appendEntry(new TestEntry(true, true));
	try {
		dialog.appendEntry("containerTest/b/async", new TestEntry(true, true));
		Q_ASSERT(false);
	} catch(ContainerLockedException e) {
		qDebug() << e.what();
	}
	try {
		QAsyncSettingsContainer asyncContainer2(&dialog, "containerTest/b/async");
		Q_ASSERT(false);
	} catch(ContainerLockedException e) {
		qDebug() << e.what();
	}
	try {
		QSettingsContainer container3(&dialog, "containerTest/b/async");
		container3.appendEntry(new TestEntry(true, false));
		Q_ASSERT(false);
	} catch(ContainerLockedException e) {
		qDebug() << e.what();
	}

	//layout tests
	QSettingsLayout dialogLayout = QSettingsLayout::dialogLayout(&dialog);
	dialogLayout.createElement(1, "layoutCategory");
	dialogLayout.moveElement(0, 2);
	dialogLayout.moveElement(1, 0);

	QSettingsLayout categoryLayout = dialogLayout.elementAt(1);
	categoryLayout.createElement(0, "elem0");
	categoryLayout.createElement(1, "elem1");
	categoryLayout.createElement(2, "elem2");
	categoryLayout.createElement(3, "elem3");
	categoryLayout.removeElement(2);
	categoryLayout.setName("Layout Test");
	try {
		categoryLayout.setOptional(true);
		Q_ASSERT(false);
	} catch(LayoutPropertyNotDefinedException e) {
		qDebug() << e.what();
	}
	Q_ASSERT(categoryLayout.defaultElement(false).isNull());
	Q_ASSERT(!categoryLayout.defaultElement(true).isNull());

	QSettingsLayout sectionLayout = categoryLayout.elementAt(2);
	sectionLayout.setName("Look here!");
	sectionLayout.setIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));
	sectionLayout.createOptionalElement(0, "group2");
	sectionLayout.createOptionalElement(0, "group1", QString(), true);
	sectionLayout.createOptionalElement(0, "group0");
	try {
		sectionLayout.createElement(0, "42z");
		Q_ASSERT(false);
	} catch(LayoutPropertyNotDefinedException e) {
		qDebug() << e.what();
	}

	QSettingsLayout groupLayout = sectionLayout.elementAt(0);
	groupLayout.setOptional(true);
	try {
		sectionLayout.createElement(0, "42z");
		Q_ASSERT(false);
	} catch(LayoutPropertyNotDefinedException e) {
		qDebug() << e.what();
	}

	QSettingsLayout transferToCategory = dialogLayout.elementAt(2);
	categoryLayout.transferElement(0, transferToCategory, 1);

	//test container from layout
	QSettingsContainer layoutContainer(&dialog, groupLayout.containerPath());
	layoutContainer.appendEntry(new TestEntry(false, false));
	layoutContainer.appendEntry(new TestEntry(false, false));

	dialog.openSettings();
	dialog.execSettings();
	return a.exec();
}
