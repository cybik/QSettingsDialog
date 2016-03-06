#include <QApplication>
#include <QDirIterator>
#include "qsettingsdialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;

	dialog.addCategory("Test1", QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	dialog.addCategory("Test2", QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));
	dialog.addCategory("Test3");
	dialog.moveCategory(0, 2);//2, 3, 1
	dialog.moveCategory(2, 1);//2, 1, 3
	dialog.deleteCategory(1);//2, 3

	dialog.showDialog();

//	QDirIterator it(":/", QDirIterator::Subdirectories);
//	while(it.hasNext())
//		qDebug(qPrintable(it.next()));

	return a.exec();
}
