#include "StdAfx.h"
#include "ObjectTriangle.h"
#include <GL/glut.h>
#include <math.h>

ObjectTriangle::ObjectTriangle() : BaseObject()
{
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;

	rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;

	scale[0] = 1.0;
	scale[1] = 1.0;
	scale[2] = 1.0;
}

ObjectTriangle::ObjectTriangle(float posX, float posY, float posZ, 
								float rotX, float rotY, float rotZ, 
								float sizeX, float sizeY, float sizeZ,
								float colorR, float colorG, float colorB) 
	: BaseObject()
{
	color[0] = colorR;
	color[1] = colorG;
	color[2] = colorB;

	position[0] = posX;
	position[1] = posY;
	position[2] = posZ;

	rotation[0] = rotX;
	rotation[1] = rotY;
	rotation[2] = rotZ;

	scale[0] = sizeX;
	scale[1] = sizeY;
	scale[2] = sizeZ;
}

ObjectTriangle::~ObjectTriangle(void)
{
}

//calculate triangle based on XY-scale 
void ObjectTriangle::Draw()
{
	glBegin(GL_TRIANGLES);
		glColor3f(color[0], color[1], color[2]);
		glVertex3f(position[0] - scale[0] * 0.5,	position[1] + scale[1] * 0.5,	position[2]);
		glVertex3f(position[0] + scale[0] * 0.5,	position[1] + scale[1] * 0.5,	position[2]);
		glVertex3f(position[0],						position[1] - scale[1] * 0.5,	position[2]);
	glEnd();
}

void ObjectTriangle::Update()
{

}
