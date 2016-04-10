#ifndef ENUMOBJECT_H
#define ENUMOBJECT_H

#include <QObject>

class EnumObject : public QObject
{
	Q_OBJECT
public:
	enum DemoEnum {
		SomeEnumValue0,
		SomeEnumValue1,
		SomeEnumValue3 = 3
	};
	Q_ENUM(DemoEnum)

	explicit EnumObject(QObject *parent = 0);

signals:

public slots:
};

#endif // ENUMOBJECT_H
