#include "qtexception.h"

QtException::QtException(const QString &what, int code) :
	std::exception(),
	error(what),
	eCode(code)
{}

QString QtException::qWhat() const
{
	return this->error;
}

int QtException::code() const
{
	return this->eCode;
}

const char *QtException::what() const
{
	return this->error.toLocal8Bit().constData();
}
