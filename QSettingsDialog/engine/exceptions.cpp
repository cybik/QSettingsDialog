#include "exceptions.h"

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}

ContainerLockedException::ContainerLockedException() :
	QtException("Container is locked! Only the locker can access it")
{}
