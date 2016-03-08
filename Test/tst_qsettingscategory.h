#ifndef QSETTINGSCATEGORYTEST_H
#define QSETTINGSCATEGORYTEST_H

#include <QObject>
#include "qsettingscategory.h"

class QSettingsCategoryTest : public QObject
{
	Q_OBJECT
public:
	explicit QSettingsCategoryTest(bool withDefault, QObject *parent = 0);

private slots:
	void initTestCase();
	void cleanupTestCase();

	void testEmpty();

	void testSectionsInsert_data();
	void testSectionsInsert();

	void testSectionsPositons_data();
	void testSectionsPositons();

	void testSectionsMove_data();
	void testSectionsMove();

	void testSectionsPositons2_data();
	void testSectionsPositons2();

	void testSectionsDelete_data();
	void testSectionsDelete();

private:
	const bool withDefault;
	QSettingsCategory *category;

	QHash<QString, QSettingsSection*> sectMap;
};

#endif // QSETTINGSCATEGORYTEST_H
