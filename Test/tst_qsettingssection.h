#ifndef QSETTINGSSECTIONTEST_H
#define QSETTINGSSECTIONTEST_H

#include <QObject>
#include "qsettingsdialog.h"

class QSettingsSectionTest : public QObject
{
	Q_OBJECT
public:
	explicit QSettingsSectionTest(bool withDefault, QObject *parent = 0);

private slots:
	void initTestCase();
	void cleanupTestCase();

	void testEmpty();

	void testGroupsInsert_data();
	void testGroupsInsert();

	void testGroupsPositons_data();
	void testGroupsPositons();

	void testGroupsMove_data();
	void testGroupsMove();

	void testGroupsPositons2_data();
	void testGroupsPositons2();

	void testGroupsTransfer_data();
	void testGroupsTransfer();

	void testGroupsPositons3_data();
	void testGroupsPositons3();

	void testGroupsDelete_data();
	void testGroupsDelete();

private:
	const bool withDefault;
	QSettingsDialog *dialog;
	QSettingsSection *section;
	QSettingsSection *transSect;

	QHash<QString, QSettingsGroup*> groupMap;
};

#endif // QSETTINGSSECTIONTEST_H
