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

float* BaseObject::GetColor()
{
	return color;
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

void BaseObject::SetPosition(float xPos, float yPos, float zPos)
{
	position[0] = xPos;
	position[1] = yPos;
	position[2] = zPos;
}

void BaseObject::SetRotation(float xRot, float yRot, float zRot)
{
	rotation[0] = xRot;
	rotation[1] = yRot;
	rotation[2] = zRot;
}

void BaseObject::SetScale(float xScale, float yScale, float zScale)
{
	scale[0] += xScale;
	scale[1] += yScale;
	scale[2] += zScale;
}
void BaseObject::SetColor(float rColor, float gColor, float bColor)
{
	color[0] += rColor;
	color[1] += gColor;
	color[2] += bColor;
}
