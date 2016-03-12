#include "tst_qsettingscategory.h"
#include "testglobal.h"
#include "qsettingscategory.h"
#include "qsettingssection.h"

#define SEC(name) this->sectMap[name]

QSettingsCategoryTest::QSettingsCategoryTest(bool withDefault, QObject *parent) :
	QObject(parent),
	dialog(Q_NULLPTR),
	withDefault(withDefault),
	category(Q_NULLPTR),
	transCat(Q_NULLPTR),
	sectMap()
{}

void QSettingsCategoryTest::initTestCase()
{
	this->dialog = new QSettingsDialog(Q_NULLPTR);
	this->category = this->dialog->defaultCategory();
	this->transCat = this->dialog->addCategory("transCat");
	if(this->withDefault) {
	   this->category->defaultSection();
	   this->transCat->defaultSection();
	}
}

void QSettingsCategoryTest::cleanupTestCase()
{
	this->sectMap.clear();
	this->dialog->deleteLater();
}

void QSettingsCategoryTest::testEmpty()
{
	QCOMPARE(this->category->hasDefaultSection(), this->withDefault);
	QCOMPARE(this->category->sectionCount(), 0);
	QVERIFY(this->category->sections(false).isEmpty());
	QCOMPARE(this->category->sections(true).size(), this->withDefault ? 1 : 0);
	QCOMPARE(this->category->sectionIndex(Q_NULLPTR), -1);
}

void QSettingsCategoryTest::testSectionsInsert_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("name");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("sect0") << 0 << "sect0" << 0;
	QTest::newRow("sect2") << 1 << "sect2" << 1;
	QTest::newRow("sect4") << -1 << "sect4" << 2;
	QTest::newRow("sect3") << 2 << "sect3" << 3;
	QTest::newRow("sect1") << 1 << "sect1" << 4;
}

void QSettingsCategoryTest::testSectionsInsert()
{
	QFETCH(int, index);
	QFETCH(QString, name);
	QFETCH(int, prevCount);

	QCOMPARE(this->category->sectionCount(), prevCount);

	QSettingsSection *sect = Q_NULLPTR;
	if(index == -1) {
		index = this->category->sectionCount();
		sect = this->category->addSection(name);
	} else
		sect = this->category->insertSection(index, name);
	QVERIFY(sect);

	QCOMPARE(this->category->sectionCount(), prevCount + 1);

	QCONTAINS(this->category->sections(), sect);
	QCOMPARE(this->category->sectionIndex(sect), index);
	QCOMPARE(this->category->sectionIndex(Q_NULLPTR), -1);
	QCOMPARE(this->category->sectionAt(index), sect);

	QCOMPARE(sect->name(), name);

	if(this->withDefault)
		QCOMPARE(this->category->sections(true).first(), this->category->defaultSection());

	this->sectMap.insert(name, sect);
}

void QSettingsCategoryTest::testSectionsPositons_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("section");

	QTest::newRow("sect0") << 0 << "sect0";
	QTest::newRow("sect1") << 1 << "sect1";
	QTest::newRow("sect2") << 2 << "sect2";
	QTest::newRow("sect3") << 3 << "sect3";
	QTest::newRow("sect4") << 4 << "sect4";
}

void QSettingsCategoryTest::testSectionsPositons()
{
	QFETCH(int, index);
	QFETCH(QString, section);

	QCOMPARE(this->category->sectionIndex(SEC(section)), index);
	QCOMPARE(this->category->sectionAt(index), SEC(section));
	QCOMPARE(SEC(section)->name(), section);
}

void QSettingsCategoryTest::testSectionsMove_data()
{
	QTest::addColumn<int>("indexFrom");
	QTest::addColumn<int>("indexTo");

	QTest::newRow("sect0") << 0 << 4;
	QTest::newRow("sect1") << 1 << 2;
	QTest::newRow("sect2") << 2 << 0;
	QTest::newRow("sect3") << 3 << 3;
	QTest::newRow("sect4") << 4 << 1;

	QTest::newRow("sect4_back") << 1 << 4;
	QTest::newRow("sect3_back") << 3 << 3;
	QTest::newRow("sect2_back") << 0 << 2;
	QTest::newRow("sect1_back") << 2 << 1;
	QTest::newRow("sect0_back") << 4 << 0;
}

void QSettingsCategoryTest::testSectionsMove()
{
	QFETCH(int, indexFrom);
	QFETCH(int, indexTo);

	QList<QSettingsSection*> oldPos = this->category->sections(false);
	QList<QSettingsSection*> oldPosW = this->category->sections(true);

	oldPos.move(indexFrom, indexTo);
	oldPosW.move(indexFrom + (this->withDefault ? 1 : 0),
				 indexTo + (this->withDefault ? 1 : 0));
	this->category->moveSection(indexFrom, indexTo);

	QCOMPARE(this->category->sections(false), oldPos);
	QCOMPARE(this->category->sections(true), oldPosW);
	if(this->withDefault)
		QCOMPARE(this->category->sections(true).first(), this->category->defaultSection());
}

void QSettingsCategoryTest::testSectionsPositons2_data()
{
	this->testSectionsPositons_data();
}

void QSettingsCategoryTest::testSectionsPositons2()
{
	this->testSectionsPositons();
}

void QSettingsCategoryTest::testSectionsTransfer_data()
{
	QTest::addColumn<bool>("direction");
	QTest::addColumn<int>("indexFrom");
	QTest::addColumn<int>("indexTo");

	QTest::newRow("sect0") << true << 0 << 0;
	QTest::newRow("sect1") << true << 0 << 0;
	QTest::newRow("sect2") << true << 0 << 2;
	QTest::newRow("sect3") << true << 0 << 1;
	QTest::newRow("sect4") << true << 0 << 3;

	QTest::newRow("sect4_back") << false << 3 << 0;
	QTest::newRow("sect3_back") << false << 1 << 0;
	QTest::newRow("sect2_back") << false << 2 << 0;
	QTest::newRow("sect1_back") << false << 0 << 0;
	QTest::newRow("sect0_back") << false << 0 << 0;
}

void QSettingsCategoryTest::testSectionsTransfer()
{
	QFETCH(bool, direction);
	QFETCH(int, indexFrom);
	QFETCH(int, indexTo);

	QList<QSettingsSection*> oldPos = this->category->sections(false);
	QList<QSettingsSection*> oldPosW = this->category->sections(true);
	QList<QSettingsSection*> newPos = this->transCat->sections(false);
	QList<QSettingsSection*> newPosW = this->transCat->sections(true);

	if(direction) {
		QSettingsSection *s = oldPos.takeAt(indexFrom);
		oldPosW.removeAt(indexFrom + (this->withDefault ? 1 : 0));
		newPos.insert(indexTo, s);
		newPosW.insert(indexTo + (this->withDefault ? 1 : 0), s);
		this->category->transferSection(indexFrom, this->transCat, indexTo);
	} else {
		QSettingsSection *s = newPos.takeAt(indexFrom);
		newPosW.removeAt(indexFrom + (this->withDefault ? 1 : 0));
		oldPos.insert(indexTo, s);
		oldPosW.insert(indexTo + (this->withDefault ? 1 : 0), s);
		this->transCat->transferSection(indexFrom, this->category, indexTo);
	}

	QCOMPARE(this->category->sections(false), oldPos);
	QCOMPARE(this->category->sections(true), oldPosW);
	QCOMPARE(this->transCat->sections(false), newPos);
	QCOMPARE(this->transCat->sections(true), newPosW);
	if(this->withDefault) {
		QCOMPARE(this->category->sections(true).first(), this->category->defaultSection());
		QCOMPARE(this->transCat->sections(true).first(), this->transCat->defaultSection());
	}
}

void QSettingsCategoryTest::testSectionsPositons3_data()
{
	this->testSectionsPositons_data();
}

void QSettingsCategoryTest::testSectionsPositons3()
{
	this->testSectionsPositons();
}

void QSettingsCategoryTest::testSectionsDelete_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("section");
	QTest::addColumn<bool>("useIndex");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("sect0") << 0 << "sect0" << true << 5;
	QTest::newRow("sect1") << 0 << "sect1" << false << 4;
	QTest::newRow("sect4") << 2 << "sect4" << true << 3;
	QTest::newRow("sect3") << 1 << "sect3" << true << 2;
	QTest::newRow("sect2") << 0 << "sect2" << false << 1;
}

void QSettingsCategoryTest::testSectionsDelete()
{
	QFETCH(int, index);
	QFETCH(QString, section);
	QFETCH(bool, useIndex);
	QFETCH(int, prevCount);

	QCOMPARE(this->category->sectionCount(), prevCount);
	QCOMPARE(this->category->sectionIndex(SEC(section)), index);

	if(useIndex)
		this->category->deleteSection(index);
	else
		QVERIFY(this->category->deleteSection(SEC(section)));

	QCOMPARE(this->category->sectionCount(), prevCount - 1);

	QCOMPARE(this->category->sectionIndex(SEC(section)), -1);
}
