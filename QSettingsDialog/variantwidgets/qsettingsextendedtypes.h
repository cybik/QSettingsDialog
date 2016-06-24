#ifndef QSETTINGSEXTENDEDTYPES_H
#define QSETTINGSEXTENDEDTYPES_H

#include <QString>
#include <QObject>
#include <QVariant>

class FilePath : public QString
{
public:
	template <typename... Args>
	FilePath(Args... args) :
		QString(args...)
	{}

	operator QVariant() {
		return (QString)*this;
	}
};

class IntRange
{
public:
	IntRange(int value = 0) :
		value(value)
	{}

	operator int() {
		return this->value;
	}

	operator QVariant() {
		return this->value;
	}

	IntRange &operator=(int value) {
		this->value = value;
		return (*this);
	}

private:
	int value;
};

class HtmlText : public QString
{
public:
	template <typename... Args>
	HtmlText(Args... args) :
		QString(args...)
	{}

	operator QVariant() {
		return (QString)*this;
	}
};

Q_DECLARE_METATYPE(FilePath)
Q_DECLARE_METATYPE(IntRange)
Q_DECLARE_METATYPE(HtmlText)

#endif // QSETTINGSEXTENDEDTYPES_H
