#ifndef METAWRAPPER_H
#define METAWRAPPER_H

#include <QObject>

class MetaWrapper : public QObject
{
	Q_OBJECT
public:
	enum TestEnum {
		Value0,
		Value1,
		Value2,
		Value3,
		Value42 = 42
	};
	Q_ENUM(TestEnum)

	enum TestFlag {
		Flag0 = 0x00,
		Flag1 = 0x01,
		Flag2 = 0x02,
		Flag3 = (Flag1 | Flag2),
		Flag8 = 0x08,
		Flag16 = 0x10,
		Flag34 = (0x20 | Flag2)
	};
	Q_DECLARE_FLAGS(TestFlags, TestFlag)
	Q_FLAG(TestFlags)

	explicit MetaWrapper(QObject *parent = 0);
};

#endif // METAWRAPPER_H
