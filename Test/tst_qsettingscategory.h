#ifndef QSETTINGSCATEGORYTEST_H
#define QSETTINGSCATEGORYTEST_H

#include <QObject>
#include "qsettingsdialog.h"

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

	void testSectionsTransfer_data();
	void testSectionsTransfer();

	void testSectionsPositons3_data();
	void testSectionsPositons3();

	void testSectionsDelete_data();
	void testSectionsDelete();

private:
	const bool withDefault;
	QSettingsDialog *dialog;
	QSettingsCategory *category;
	QSettingsCategory *transCat;

	QHash<QString, QSettingsSection*> sectMap;
};

#endif // QSETTINGSCATEGORYTEST_H
