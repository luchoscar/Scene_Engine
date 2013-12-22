#include "StdAfx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
	delete(ib);
	delete(vb);
	delete(nb);
	delete(cb);
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