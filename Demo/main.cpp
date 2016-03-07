#include <QApplication>
#include <QDirIterator>
#include "qsettingsdialog.h"
#include "qsettingscategory.h"
#include "qsettingssection.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;
	dialog.defaultGroup();

	//categories
	dialog.addCategory("Test1", QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"))->defaultSection();
	QSettingsCategory *cat2 = dialog.addCategory("Test2", QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	QSettingsCategory *cat3 = dialog.addCategory("Test3");
	dialog.moveCategory(0, 2);//2, 3, 1
	dialog.moveCategory(2, 1);//2, 1, 3
	dialog.deleteCategory(1);//2, 3

	cat2->setToolTip("Hallo Baum");
	cat3->setName("Baum == 42");

	//sections
	cat3->defaultSection();

	cat2->addSection("Test1", QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"))->defaultGroup();
	QSettingsSection *sec2 = cat2->addSection("Test2");
	QSettingsSection *sec3 = cat2->addSection("Test3", QIcon(":/qt-project.org/styles/commonstyle/images/floppy-32.png"));
	cat2->moveSection(0, 2);//2, 3, 1
	cat2->moveSection(2, 1);//2, 1, 3
	cat2->deleteSection(1);//2, 3

	cat2->defaultSection();
	sec2->setIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	sec3->setName("Baum == 42");

	dialog.showDialog();

//	QDirIterator it(":/", QDirIterator::Subdirectories);
//	while(it.hasNext())
//		qDebug(qPrintable(it.next()));

	return a.exec();
}
