#ifndef QSETTINGSDIALOGTEST_H
#define QSETTINGSDIALOGTEST_H

#include <QObject>
#include "qsettingsdialog.h"

class QSettingsDialogTest : public QObject
{
	Q_OBJECT
public:
	explicit QSettingsDialogTest(bool withDefault, QObject *parent = 0);

private slots:
	void initTestCase();
	void cleanupTestCase();

	void testEmpty();

	void testCategoriesInsert_data();
	void testCategoriesInsert();

	void testCategoriesPositons_data();
	void testCategoriesPositons();

	void testCategoriesMove_data();
	void testCategoriesMove();

	void testCategoriesPositons2_data();
	void testCategoriesPositons2();

	void testCategoriesDelete_data();
	void testCategoriesDelete();

private:
	const bool withDefault;
	QSettingsDialog *dialog;

	QHash<QString, QSettingsCategory*> catMap;
};

#endif // QSETTINGSDIALOGTEST_H
