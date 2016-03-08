#ifndef CATEGORYTEST_H
#define CATEGORYTEST_H

#include <QObject>

class CategoryTest : public QObject
{
	Q_OBJECT

public:
	CategoryTest();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void testDefault();
};

#endif // CATEGORYTEST_H
