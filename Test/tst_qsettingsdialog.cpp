#include "tst_qsettingsdialog.h"
#include "testglobal.h"
#include "qsettingscategory.h"

#define CAT(name) this->catMap[name]

QSettingsDialogTest::QSettingsDialogTest(bool withDefault, QObject *parent) :
	QObject(parent),
	withDefault(withDefault),
	dialog(Q_NULLPTR),
	catMap()
{}

void QSettingsDialogTest::initTestCase()
{
	this->dialog = new QSettingsDialog(this);
	if(this->withDefault)
		this->dialog->defaultCategory();
}

void QSettingsDialogTest::cleanupTestCase()
{
	this->dialog->deleteLater();
	this->catMap.clear();
}

void QSettingsDialogTest::testEmpty()
{
	QCOMPARE(this->dialog->hasDefaultCategory(), this->withDefault);
	QCOMPARE(this->dialog->categoryCount(), 0);
	QVERIFY(this->dialog->categories(false).isEmpty());
	QCOMPARE(this->dialog->categories(true).size(), this->withDefault ? 1 : 0);
	QCOMPARE(this->dialog->categoryIndex(Q_NULLPTR), -1);
}

void QSettingsDialogTest::testCategoriesInsert_data()
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

void QSettingsDialogTest::testCategoriesInsert()
{
	QFETCH(int, index);
	QFETCH(QString, name);
	QFETCH(int, prevCount);

	QCOMPARE(this->dialog->categoryCount(), prevCount);

	QSettingsCategory *cat = Q_NULLPTR;
	if(index == -1) {
		index = this->dialog->categoryCount();
		cat = this->dialog->addCategory(name);
	} else
		cat = this->dialog->insertCategory(index, name);
	QVERIFY(cat);

	QCOMPARE(this->dialog->categoryCount(), prevCount + 1);

	QCONTAINS(this->dialog->categories(), cat);
	QCOMPARE(this->dialog->categoryIndex(cat), index);
	QCOMPARE(this->dialog->categoryIndex(Q_NULLPTR), -1);
	QCOMPARE(this->dialog->categoryAt(index), cat);

	QCOMPARE(cat->name(), name);

	if(this->withDefault)
		QCOMPARE(this->dialog->categories(true).first(), this->dialog->defaultCategory());

	this->catMap.insert(name, cat);
}

void QSettingsDialogTest::testCategoriesPositons_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("category");

	QTest::newRow("cat0") << 0 << "cat0";
	QTest::newRow("cat1") << 1 << "cat1";
	QTest::newRow("cat2") << 2 << "cat2";
	QTest::newRow("cat3") << 3 << "cat3";
	QTest::newRow("cat4") << 4 << "cat4";
}

void QSettingsDialogTest::testCategoriesPositons()
{
	QFETCH(int, index);
	QFETCH(QString, category);

	QCOMPARE(this->dialog->categoryIndex(CAT(category)), index);
	QCOMPARE(this->dialog->categoryAt(index), CAT(category));
	QCOMPARE(CAT(category)->name(), category);
}

void QSettingsDialogTest::testCategoriesMove_data()
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

void QSettingsDialogTest::testCategoriesMove()
{
	QFETCH(int, indexFrom);
	QFETCH(int, indexTo);

	QList<QSettingsCategory*> oldPos = this->dialog->categories(false);
	QList<QSettingsCategory*> oldPosW = this->dialog->categories(true);

	oldPos.move(indexFrom, indexTo);
	oldPosW.move(indexFrom + (this->withDefault ? 1 : 0),
				 indexTo + (this->withDefault ? 1 : 0));
	this->dialog->moveCategory(indexFrom, indexTo);

	QCOMPARE(this->dialog->categories(false), oldPos);
	QCOMPARE(this->dialog->categories(true), oldPosW);
	if(this->withDefault)
		QCOMPARE(this->dialog->categories(true).first(), this->dialog->defaultCategory());
}

void QSettingsDialogTest::testCategoriesPositons2_data()
{
	this->testCategoriesPositons_data();
}

void QSettingsDialogTest::testCategoriesPositons2()
{
	this->testCategoriesPositons();
}

void QSettingsDialogTest::testCategoriesDelete_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("category");
	QTest::addColumn<bool>("useIndex");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("cat0") << 0 << "cat0" << true << 5;
	QTest::newRow("cat1") << 0 << "cat1" << false << 4;
	QTest::newRow("cat4") << 2 << "cat4" << true << 3;
	QTest::newRow("cat3") << 1 << "cat3" << true << 2;
	QTest::newRow("cat2") << 0 << "cat2" << false << 1;
}

void QSettingsDialogTest::testCategoriesDelete()
{
	QFETCH(int, index);
	QFETCH(QString, category);
	QFETCH(bool, useIndex);
	QFETCH(int, prevCount);

	QCOMPARE(this->dialog->categoryCount(), prevCount);
	QCOMPARE(this->dialog->categoryIndex(CAT(category)), index);

	if(useIndex)
		this->dialog->deleteCategory(index);
	else
		QVERIFY(this->dialog->deleteCategory(CAT(category)));

	QCOMPARE(this->dialog->categoryCount(), prevCount - 1);

	QCOMPARE(this->dialog->categoryIndex(CAT(category)), -1);
}
