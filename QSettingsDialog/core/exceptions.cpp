#include "exceptions.h"

InvalidContainerPathException::InvalidContainerPathException() :
	QtException("Invalid container format!")
{}

LayoutPropertyNotDefinedException::LayoutPropertyNotDefinedException() :
	QtException("The layout property you are trying to access is not defined for the current layout type")
{}

InvalidTargetLayoutException::InvalidTargetLayoutException() :
	QtException("The target layout container is either empty or of an invalid layout type")
{}
