#ifndef ENUMOBJECT_H
#define ENUMOBJECT_H

#include <QObject>

class EnumObject : public QObject
{
	Q_OBJECT

	Q_PROPERTY(DemoFlags name READ name WRITE setName NOTIFY nameChanged)

public:
	enum DemoEnum {
		SomeEnumValue0,
		SomeEnumValue1,
		SomeEnumValue3 = 3
	};
	Q_ENUM(DemoEnum)

	enum DemoFlag {
		SomeFlag0 = 0x00,
		SomeFlag1 = 0x01,
		SomeFlag2 = 0x02,
		SomeFlag3 = 0x03
	};
	Q_DECLARE_FLAGS(DemoFlags, DemoFlag)
	Q_FLAG(DemoFlags)

	explicit EnumObject(QObject *parent = 0);

	DemoFlags name() const
	{
		return m_name;
	}

signals:

	void nameChanged(DemoFlags name);

public slots:
	void setName(DemoFlags name)
	{
		if (m_name == name)
			return;

		m_name = name;
		emit nameChanged(name);
	}

private:
	DemoFlags m_name;
};

#endif // ENUMOBJECT_H
