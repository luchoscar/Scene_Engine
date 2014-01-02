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

void BaseObject::TranslateOnAxis(float xPos, float yPos, float zPos)
{
	position[0] += xPos;
	position[1] += yPos;
	position[2] += zPos;
}

void BaseObject::RotationAroundAxis(float xRot, float yRot, float zRot)
{
	rotation[0] += xRot;
	rotation[1] += yRot;
	rotation[2] += zRot;
}