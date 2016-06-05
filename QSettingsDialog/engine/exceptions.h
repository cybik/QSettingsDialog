#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "qsettingsdialog_global.h"
#include "qtexception.h"

class QSETTINGSDIALOGSHARED_EXPORT InvalidContainerPathException : public QtException
{
public:
	InvalidContainerPathException();
};

class QSETTINGSDIALOGSHARED_EXPORT ContainerLockedException : public QtException
{
public:
	ContainerLockedException();
};

#endif // EXCEPTIONS_H
