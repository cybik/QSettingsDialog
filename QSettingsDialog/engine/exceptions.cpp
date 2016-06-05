#include "exceptions.h"

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}

ContainerLockedException::ContainerLockedException() :
	QtException("Container is already locked!")
{}
