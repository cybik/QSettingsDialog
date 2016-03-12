#include <QApplication>
#include <QDirIterator>
#include "qsettingsdialog.h"
#include "qsettingscategory.h"
#include "qsettingssection.h"
#include "qsettingsgroup.h"
#include "qsettingsvariantentry.h"

#include <QVariant>
#include "commandsettingsentry.h"
#include "typeloader.h"

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
	tGrp->addEntry(new QSettingsVariantEntry("QString", false, new TypeLoader<QString>("default")));
	tGrp->addEntry(new QSettingsVariantEntry("QByteArray", false, new TypeLoader<QByteArray>("default")));
	tGrp->addEntry(new QSettingsVariantEntry("bool", false, new TypeLoader<bool>(true)));

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
