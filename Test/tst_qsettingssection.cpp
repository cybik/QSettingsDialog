#include "tst_qsettingssection.h"
#include "testglobal.h"
#include "qsettingscategory.h"
#include "qsettingssection.h"
#include "qsettingsgroup.h"

#define GRP(name) this->groupMap[name]

QSettingsSectionTest::QSettingsSectionTest(bool withDefault, QObject *parent) :
	QObject(parent),
	dialog(Q_NULLPTR),
	withDefault(withDefault),
	section(Q_NULLPTR),
	transSect(Q_NULLPTR),
	groupMap()
{}

void QSettingsSectionTest::initTestCase()
{
	this->dialog = new QSettingsDialog(Q_NULLPTR);
	this->section = this->dialog->defaultSection();
	this->transSect = this->dialog->defaultCategory()->addSection("transSect");
	if(this->withDefault) {
	   this->section->defaultGroup();
	   this->transSect->defaultGroup();
	}
}

void QSettingsSectionTest::cleanupTestCase()
{
	this->groupMap.clear();
	this->dialog->deleteLater();
}

void QSettingsSectionTest::testEmpty()
{
	QCOMPARE(this->section->hasDefaultGroup(), this->withDefault);
	QCOMPARE(this->section->groupCount(), 0);
	QVERIFY(this->section->groups(false).isEmpty());
	QCOMPARE(this->section->groups(true).size(), this->withDefault ? 1 : 0);
	QCOMPARE(this->section->groupIndex(Q_NULLPTR), -1);
}

void QSettingsSectionTest::testGroupsInsert_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("name");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("grp0") << 0 << "grp0" << 0;
	QTest::newRow("grp2") << 1 << "grp2" << 1;
	QTest::newRow("grp4") << -1 << "grp4" << 2;
	QTest::newRow("grp3") << 2 << "grp3" << 3;
	QTest::newRow("grp1") << 1 << "grp1" << 4;
}

void QSettingsSectionTest::testGroupsInsert()
{
	QFETCH(int, index);
	QFETCH(QString, name);
	QFETCH(int, prevCount);

	QCOMPARE(this->section->groupCount(), prevCount);

	QSettingsGroup *sect = Q_NULLPTR;
	if(index == -1) {
		index = this->section->groupCount();
		sect = this->section->addGroup(name);
	} else
		sect = this->section->insertGroup(index, name);
	QVERIFY(sect);

	QCOMPARE(this->section->groupCount(), prevCount + 1);

	QCONTAINS(this->section->groups(), sect);
	QCOMPARE(this->section->groupIndex(sect), index);
	QCOMPARE(this->section->groupIndex(Q_NULLPTR), -1);
	QCOMPARE(this->section->groupAt(index), sect);

	QCOMPARE(sect->name(), name);

	if(this->withDefault)
		QCOMPARE(this->section->groups(true).first(), this->section->defaultGroup());

	this->groupMap.insert(name, sect);
}

void QSettingsSectionTest::testGroupsPositons_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("group");

	QTest::newRow("grp0") << 0 << "grp0";
	QTest::newRow("grp1") << 1 << "grp1";
	QTest::newRow("grp2") << 2 << "grp2";
	QTest::newRow("grp3") << 3 << "grp3";
	QTest::newRow("grp4") << 4 << "grp4";
}

void QSettingsSectionTest::testGroupsPositons()
{
	QFETCH(int, index);
	QFETCH(QString, group);

	QCOMPARE(this->section->groupIndex(GRP(group)), index);
	QCOMPARE(this->section->groupAt(index), GRP(group));
	QCOMPARE(GRP(group)->name(), group);
}

void QSettingsSectionTest::testGroupsMove_data()
{
	QTest::addColumn<int>("indexFrom");
	QTest::addColumn<int>("indexTo");

	QTest::newRow("grp0") << 0 << 4;
	QTest::newRow("grp1") << 1 << 2;
	QTest::newRow("grp2") << 2 << 0;
	QTest::newRow("grp3") << 3 << 3;
	QTest::newRow("grp4") << 4 << 1;

	QTest::newRow("grp4_back") << 1 << 4;
	QTest::newRow("grp3_back") << 3 << 3;
	QTest::newRow("grp2_back") << 0 << 2;
	QTest::newRow("grp1_back") << 2 << 1;
	QTest::newRow("grp0_back") << 4 << 0;
}

void QSettingsSectionTest::testGroupsMove()
{
	QFETCH(int, indexFrom);
	QFETCH(int, indexTo);

	QList<QSettingsGroup*> oldPos = this->section->groups(false);
	QList<QSettingsGroup*> oldPosW = this->section->groups(true);

	oldPos.move(indexFrom, indexTo);
	oldPosW.move(indexFrom + (this->withDefault ? 1 : 0),
				 indexTo + (this->withDefault ? 1 : 0));
	this->section->moveGroup(indexFrom, indexTo);

	QCOMPARE(this->section->groups(false), oldPos);
	QCOMPARE(this->section->groups(true), oldPosW);
	if(this->withDefault)
		QCOMPARE(this->section->groups(true).first(), this->section->defaultGroup());
}

void QSettingsSectionTest::testGroupsPositons2_data()
{
	this->testGroupsPositons_data();
}

void QSettingsSectionTest::testGroupsPositons2()
{
	this->testGroupsPositons();
}

void QSettingsSectionTest::testGroupsTransfer_data()
{
	QTest::addColumn<bool>("direction");
	QTest::addColumn<int>("indexFrom");
	QTest::addColumn<int>("indexTo");

	QTest::newRow("grp0") << true << 0 << 0;
	QTest::newRow("grp1") << true << 0 << 0;
	QTest::newRow("grp2") << true << 0 << 2;
	QTest::newRow("grp3") << true << 0 << 1;
	QTest::newRow("grp4") << true << 0 << 3;

	QTest::newRow("grp4_back") << false << 3 << 0;
	QTest::newRow("grp3_back") << false << 1 << 0;
	QTest::newRow("grp2_back") << false << 2 << 0;
	QTest::newRow("grp1_back") << false << 0 << 0;
	QTest::newRow("grp0_back") << false << 0 << 0;
}

void QSettingsSectionTest::testGroupsTransfer()
{
	QFETCH(bool, direction);
	QFETCH(int, indexFrom);
	QFETCH(int, indexTo);

	QList<QSettingsGroup*> oldPos = this->section->groups(false);
	QList<QSettingsGroup*> oldPosW = this->section->groups(true);
	QList<QSettingsGroup*> newPos = this->transSect->groups(false);
	QList<QSettingsGroup*> newPosW = this->transSect->groups(true);

	if(direction) {
		QSettingsGroup *s = oldPos.takeAt(indexFrom);
		oldPosW.removeAt(indexFrom + (this->withDefault ? 1 : 0));
		newPos.insert(indexTo, s);
		newPosW.insert(indexTo + (this->withDefault ? 1 : 0), s);
		this->section->transferGroup(indexFrom, this->transSect, indexTo);
	} else {
		QSettingsGroup *s = newPos.takeAt(indexFrom);
		newPosW.removeAt(indexFrom + (this->withDefault ? 1 : 0));
		oldPos.insert(indexTo, s);
		oldPosW.insert(indexTo + (this->withDefault ? 1 : 0), s);
		this->transSect->transferGroup(indexFrom, this->section, indexTo);
	}

	QCOMPARE(this->section->groups(false), oldPos);
	QCOMPARE(this->section->groups(true), oldPosW);
	QCOMPARE(this->transSect->groups(false), newPos);
	QCOMPARE(this->transSect->groups(true), newPosW);
	if(this->withDefault) {
		QCOMPARE(this->section->groups(true).first(), this->section->defaultGroup());
		QCOMPARE(this->transSect->groups(true).first(), this->transSect->defaultGroup());
	}
}

void QSettingsSectionTest::testGroupsPositons3_data()
{
	this->testGroupsPositons_data();
}

void QSettingsSectionTest::testGroupsPositons3()
{
	this->testGroupsPositons();
}

void QSettingsSectionTest::testGroupsDelete_data()
{
	QTest::addColumn<int>("index");
	QTest::addColumn<QString>("group");
	QTest::addColumn<bool>("useIndex");
	QTest::addColumn<int>("prevCount");

	QTest::newRow("grp0") << 0 << "grp0" << true << 5;
	QTest::newRow("grp1") << 0 << "grp1" << false << 4;
	QTest::newRow("grp4") << 2 << "grp4" << true << 3;
	QTest::newRow("grp3") << 1 << "grp3" << true << 2;
	QTest::newRow("grp2") << 0 << "grp2" << false << 1;
}

void QSettingsSectionTest::testGroupsDelete()
{
	QFETCH(int, index);
	QFETCH(QString, group);
	QFETCH(bool, useIndex);
	QFETCH(int, prevCount);

	QCOMPARE(this->section->groupCount(), prevCount);
	QCOMPARE(this->section->groupIndex(GRP(group)), index);

	if(useIndex)
		this->section->deleteGroup(index);
	else
		QVERIFY(this->section->deleteGroup(GRP(group)));

	QCOMPARE(this->section->groupCount(), prevCount - 1);

	QCOMPARE(this->section->groupIndex(GRP(group)), -1);
}
