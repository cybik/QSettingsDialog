#ifndef TESTGLOBAL_H
#define TESTGLOBAL_H

#include <QtTest>

namespace TestGlobal
{
	template<typename Container, typename Type>
	inline bool gContains(const Container &container,
						  const Type &value,
						  const char *statementStr,
						  const char *description,
						  const char *file,
						  int line) {
		return QTest::qVerify(container.contains(value), statementStr, description, file, line);
	}
}

#define QCONTAINS(list, value) do {\
	if (!TestGlobal::gContains((list), (value), #list " contains " #value, "", __FILE__, __LINE__))\
		return;\
	} while (0)

#endif // TESTGLOBAL_H
