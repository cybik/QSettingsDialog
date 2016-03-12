#include "tst_qsettingscategory.h"
#include "qsettingsdialog.h"
#include "testglobal.h"
#include "qsettingssection.h"

#define SEC(name) this->sectMap[name]

QSettingsCategoryTest::QSettingsCategoryTest(bool withDefault, QObject *parent) :
	QObject(parent),
	withDefault(withDefault),
	category(Q_NULLPTR),
	sectMap()
{}

void QSettingsCategoryTest::initTestCase()
{
	this->category = (new QSettingsDialog(Q_NULLPTR))->defaultCategory();
	if(this->withDefault)
		this->category->defaultSection();
}

void QSettingsCategoryTest::cleanupTestCase()
{
	//this->category->deleteLater();
	this->sectMap.clear();
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

	QTest::newRow("cat0") << 0 << "cat0" << 0;
	QTest::newRow("cat2") << 1 << "cat2" << 1;
	QTest::newRow("cat4") << -1 << "cat4" << 2;
	QTest::newRow("cat3") << 2 << "cat3" << 3;
	QTest::newRow("cat1") << 1 << "cat1" << 4;
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

	QTest::newRow("cat0") << 0 << "cat0";
	QTest::newRow("cat1") << 1 << "cat1";
	QTest::newRow("cat2") << 2 << "cat2";
	QTest::newRow("cat3") << 3 << "cat3";
	QTest::newRow("cat4") << 4 << "cat4";
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

	QTest::newRow("cat0") << 0 << 4;
	QTest::newRow("cat1") << 1 << 2;
	QTest::newRow("cat2") << 2 << 0;
	QTest::newRow("cat3") << 3 << 3;
	QTest::newRow("cat4") << 4 << 1;

	QTest::newRow("cat4_back") << 1 << 4;
	QTest::newRow("cat3_back") << 3 << 3;
	QTest::newRow("cat2_back") << 0 << 2;
	QTest::newRow("cat1_back") << 2 << 1;
	QTest::newRow("cat0_back") << 4 << 0;
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

void QSettingsCategoryTest::testSectionsDelete_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("section");
	QTest::addColumn<bool>("useIndex");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("cat0") << 0 << "cat0" << true << 5;
	QTest::newRow("cat1") << 0 << "cat1" << false << 4;
	QTest::newRow("cat4") << 2 << "cat4" << true << 3;
	QTest::newRow("cat3") << 1 << "cat3" << true << 2;
	QTest::newRow("cat2") << 0 << "cat2" << false << 1;
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
