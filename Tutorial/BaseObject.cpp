#include "StdAfx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

float* BaseObject::GetPosition()
{
	return position;
}

float* BaseObject::GetRotation()
{
	return rotation;
}

float* BaseObject::GetScale()
{
	return scale;
}