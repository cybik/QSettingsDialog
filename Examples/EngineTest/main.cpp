#include <QApplication>
#include <QDebug>
#include <QStyle>
#include <QThread>
#include <qsettingsdialog.h>
#include <qsettingscontainer.h>
#include <qsettingslayout.h>
#include <qsettingswidgetdialogengine.h>
#include "testentry.h"
#include "delayedtestentry.h"
#include "swidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsWidgetDialogEngine::registerGlobalFactory(0, new SFactory(false));
	QSettingsWidgetDialogEngine::registerGlobalFactory(1, new SFactory(true));

	QSettingsDialog dialog;
/*\
|*| -> instead of global registering
|*| auto engine = (QSettingsWidgetDialogEngine*) dialog.displayEngine();
|*| engine->addFactory(0, new SFactory(false));
|*| engine->addFactory(1, new SFactory(true));
\*/

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

	dialog.setGroup("normal");
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(false, true, "withFixedData"));
	dialog.appendEntry(new TestEntry(true, true));
	dialog.appendEntry(new TestEntry(true, true, "withOptionalData"));

	//checking test, does auto-checking work?
	dialog.setSection("checkingTest");
	dialog.setGroup("optional1", "optional - no data", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional2", "optional - fixed data", true);
	dialog.appendEntry(new TestEntry(false, true, "fixed group data"));
	dialog.appendEntry(new TestEntry(true, true));

	dialog.setGroup("optional3", "optional - optional subdata", true);
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(true, true, "optional group data"));

	//section and group entries - mixed appeareance
	dialog.setSection("mixedEntriesTest");
	dialog.unsetGroup();
	dialog.appendEntry(new TestEntry(false, true));
	dialog.appendEntry(new TestEntry(false, true));

	dialog.setGroup("someGroup");
	dialog.appendEntry(new TestEntry(true, true, "LOOOOL"));
	dialog.appendEntry(new TestEntry(false, false));
	dialog.unsetGroup();
	dialog.appendEntry(new TestEntry(false, true, QVariant()));
	dialog.appendEntry(new TestEntry(true, false, QVariant()));

	//async test
	dialog.setSection("asyncTest");
	dialog.unsetGroup();

	dialog.appendEntry(new DelayedTestEntry("test500", 500));
	dialog.appendEntry(new DelayedTestEntry("test1000", 1000));
	dialog.appendEntry(new DelayedTestEntry("test1500", 1500));

	auto threaded = new DelayedTestEntry("testThreaded", 42);
	QThread thread;
	thread.start();
	threaded->moveToThread(&thread);
	dialog.appendEntry(threaded);

	//container test
	//TODO test more
	dialog.setContainer("containerTest/./normal");
	dialog.appendEntry(new TestEntry(false, true));

	QGroupSettingsContainer container(&dialog, "containerTest/./normal");
	container.appendEntry(new TestEntry(true, true));
	auto rem = dialog.appendEntry(new TestEntry(false, true));
	container.insertEntry(1, new TestEntry(false, false));

	QSettingsContainer *container2 = dialog.currentContainer(&dialog);
	container2->removeEntry(rem);
	dialog.prependEntry(new TestEntry(false, true));

	QGroupSettingsContainer container3(&dialog, "containerTest/./normal_trans");
	container2->transferElement(0, &container3, 0);

	QSettingsContainer *sectionContainer1 = dialog.currentSectionContainer(&dialog);
	sectionContainer1->appendEntry(new TestEntry(false, true));
	QSectionSettingsContainer sectionContainer2(&dialog, dialog.sectionContainerPath());
	sectionContainer2.moveElement(0, 2);

//	//async container test
//	QAsyncSettingsContainer asyncContainer(&dialog, "containerTest/b/async");
//	asyncContainer.appendEntry(new TestEntry(false, false));
//	dialog.appendEntry(new TestEntry(true, true));
//	try {
//		dialog.appendEntry("containerTest/b/async", new TestEntry(true, true));
//		Q_ASSERT(false);
//	} catch(ContainerLockedException e) {
//		qDebug() << e.what();
//	}
//	try {
//		QAsyncSettingsContainer asyncContainer2(&dialog, "containerTest/b/async");
//		Q_ASSERT(false);
//	} catch(ContainerLockedException e) {
//		qDebug() << e.what();
//	}
//	try {
//		QSettingsContainer container4(&dialog, "containerTest/b/async");
//		container4.appendEntry(new TestEntry(true, false));
//		Q_ASSERT(false);
//	} catch(ContainerLockedException e) {
//		qDebug() << e.what();
//	}

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
	Q_ASSERT(categoryLayout.defaultElement(false).isNull());
	Q_ASSERT(!categoryLayout.defaultElement(true).isNull());

	QSettingsLayout sectionLayout = categoryLayout.elementAt(2);
	sectionLayout.setName("Look here!");
	sectionLayout.setIcon(QApplication::style()->standardIcon(QStyle::SP_ComputerIcon));

	//test container from layout
	QSectionSettingsContainer layoutContainer(&sectionLayout);
	layoutContainer.appendEntry(new TestEntry(false, false));
	layoutContainer.appendEntry(new TestEntry(false, false));

	dialog.openSettings();
	dialog.execSettings();
	auto res = a.exec();
	thread.quit();
	thread.wait();
	return res;
}
