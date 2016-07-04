#ifndef QTEXCEPTION_H
#define QTEXCEPTION_H

#include "qsettingsdialog_global.h"
#include <exception>
#include <QString>

class QSETTINGSDIALOGSHARED_EXPORT QtException : public std::exception
{
public:
	QtException(const QString &what = QString(), int code = 0);

	QString qWhat() const;
	int code() const;
    const char *what() const noexcept final;

private:
	const QByteArray error;
	const int eCode;
};

#endif // QTEXCEPTION_H
