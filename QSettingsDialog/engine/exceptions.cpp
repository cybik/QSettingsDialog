#include "exceptions.h"

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}

ContainerLockedException::ContainerLockedException() :
	QtException("Container is locked! Only the locker can access it")
{}

LayoutPropertyNotDefinedException::LayoutPropertyNotDefinedException() :
	QtException("The layout property you are trying to access is not defined for the current layout type")
{}
