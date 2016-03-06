#include <QApplication>
#include "qsettingsdialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSettingsDialog dialog;

	return a.exec();
}
