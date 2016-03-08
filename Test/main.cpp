#include <QtTest>
#include <QHash>
#include <iostream>

#include "categorytest.h"

QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setAttribute(Qt::AA_Use96Dpi, true);
	QTEST_DISABLE_KEYPAD_NAVIGATION
	QTEST_ADD_GPU_BLACKLIST_SUPPORT
	QTEST_SET_MAIN_SOURCE_PATH

	QHash<QObject*, int> testObjects = {
		{new CategoryTest(), 0}
	};

	foreach(QObject *testObject, testObjects.keys()) {
		testObjects[testObject] = QTest::qExec(testObject, argc, argv);
	}

	int sucCount = 0;
	int failCount = 0;
	std::cout << "\n========= TOTAL RESULT =========\n";
	for(QHash<QObject*, int>::iterator it = testObjects.begin(), end = testObjects.end(); it != end; ++it) {
		std::cout << "Test: \"" << it.key()->metaObject()->className() << "\" - Result code: " << it.value() << std::endl;
		if(it.value() == 0)
			sucCount++;
		else
			failCount++;
		delete it.key();
	}
	std::cout << "Totals: " << sucCount << " successful, "
			  << failCount << " failed, "
			  << sucCount + failCount << " in total\n"
			  << "========= TOTAL RESULT =========" << std::endl;

	return 0;
}
