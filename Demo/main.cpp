#include <QApplication>
#include <QDirIterator>
#include "qsettingsdialog.h"
#include "qsettingscategory.h"
#include "qsettingssection.h"
#include "qsettingsgroup.h"
#include "qsettingsvariantentry.h"

#include <QVariant>
#include <QDateTime>
#include <QUrl>
#include "commandsettingsentry.h"
#include "typeloader.h"

#define CREATE_ENTRY(type, def) new QSettingsVariantEntry(#type, false, new TypeLoader<type>(def))
#define CREATE_ENTRY_PARAM(type, def, ...)  new QSettingsVariantEntry(#type, false, new TypeLoader<type>(def, __VA_ARGS__))

struct SomeType {};
Q_DECLARE_METATYPE(SomeType)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//Variant test
	qDebug() << "typeid" << qRegisterMetaType<SomeType>("SomeType");
	QVariant varInt = QVariant::fromValue<int>(42);
	QVariant varType = QVariant::fromValue<SomeType>(SomeType());
	qDebug() << "varInt" << (int)varInt.type() << QMetaType::type(varInt.typeName()) << varInt.typeName() << varInt.value<int>();
	qDebug() << "varType" << (int)varType.type() << QMetaType::type(varType.typeName()) << varType.typeName();// << varType.value<SomeType>();

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

	//groups
	sec3->defaultGroup();

	sec2->addGroup("Test1", false);
	QSettingsGroup *grp2 = sec2->addGroup("Test2");
	QSettingsGroup *grp3 = sec2->addGroup("Test3", true);
	sec2->moveGroup(0, 2);//2, 3, 1
	sec2->moveGroup(2, 1);//2, 1, 3
	sec2->deleteGroup(1);//2, 3

	sec2->defaultGroup();
	grp2->setOptional(true);
	grp3->setName("Baum == 42");
	grp3->setOptional(false);

	//entries
	sec2->defaultGroup()->addEntry(new CommandSettingsEntry("Test1"));
	sec2->defaultGroup()->addEntry(new CommandSettingsEntry("Test2", false));
	sec2->defaultGroup()->addEntry(new CommandSettingsEntry("Test3", false));
	grp2->addEntry(new CommandSettingsEntry("Test4"));
	grp2->addEntry(new CommandSettingsEntry("Test5", false));
	grp3->addEntry(new CommandSettingsEntry("Test5", false));

	//type tests
	QSettingsGroup *tGrp = dialog.defaultGroup();
	tGrp->addEntry(CREATE_ENTRY(bool, true));
	tGrp->addEntry(CREATE_ENTRY(int, -42));
	tGrp->addEntry(CREATE_ENTRY(unsigned int, 42));
	tGrp->addEntry(CREATE_ENTRY(double, 666.13));
	tGrp->addEntry(CREATE_ENTRY_PARAM(QString, "default", {{"placeholderText", "Baum == 42"}}));
	tGrp->addEntry(CREATE_ENTRY(QByteArray, "default"));
	tGrp->addEntry(CREATE_ENTRY(long, -42));
	tGrp->addEntry(CREATE_ENTRY(long long, -42));
	tGrp->addEntry(CREATE_ENTRY(short, -42));
	tGrp->addEntry(CREATE_ENTRY(char, -42));
	tGrp->addEntry(CREATE_ENTRY(unsigned long, 42));
	tGrp->addEntry(CREATE_ENTRY(unsigned long long, 42));
	tGrp->addEntry(CREATE_ENTRY(unsigned short, 42));
	tGrp->addEntry(CREATE_ENTRY(signed char, -42));
	tGrp->addEntry(CREATE_ENTRY(unsigned char, 42));
	tGrp->addEntry(CREATE_ENTRY(float, 666.13f));
	tGrp->addEntry(CREATE_ENTRY(QDate, QDate::currentDate()));
	tGrp->addEntry(CREATE_ENTRY(QTime, QTime::currentTime()));
	tGrp->addEntry(CREATE_ENTRY(QColor, Qt::darkCyan));
	tGrp->addEntry(CREATE_ENTRY(QStringList, QStringList()));
	tGrp->addEntry(CREATE_ENTRY(QUrl, QUrl("http://google.de")));
	tGrp->addEntry(CREATE_ENTRY(QDateTime, QDateTime::currentDateTime()));
	tGrp->addEntry(CREATE_ENTRY(QFont, QApplication::font()));
	tGrp->addEntry(CREATE_ENTRY_PARAM(QByteArrayList, QByteArrayList(), {{"buttonsVisible", false}}));

	if(dialog.exec() == 0)
		return 1;
	if(dialog.exec() == 0)
		return 1;
	if(dialog.exec() == 0)
		return 1;

//	QDirIterator it(":/", QDirIterator::Subdirectories);
//	while(it.hasNext())
//		qDebug(qPrintable(it.next()));

	return 0;
}
