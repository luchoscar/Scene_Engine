#include "StdAfx.h"
#include "ObjectTriangle.h"
#include <GL/glut.h>
#include <math.h>

ObjectTriangle::ObjectTriangle() : BaseObject()
{
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;

	position[0] = 0;
	position[1] = 0;

	rotation = 0;

	scale = 1.0;
}

ObjectTriangle::ObjectTriangle(float x, float y, float size) : BaseObject()
{
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;

	position[0] = x;
	position[1] = y;

	rotation = 0;

	scale = size * 0.5f;
}

ObjectTriangle::~ObjectTriangle(void)
{
}

void ObjectTriangle::Draw()
{
	//adjust rotation for each vertex
	//multiply by sin,cos , or something else

	glBegin(GL_TRIANGLES);
		glColor3f(color[0],color[1],color[2]);
		glVertex2f(position[0] - scale, position[1] + scale);
		glVertex2f(position[0] + scale, position[1] + scale);
		glVertex2f(position[0] + 0, position[1] - scale);
	glEnd();
}

void ObjectTriangle::Update()
{
	/*color[1] += .01;
	if (color[1] > 1.0)
	{
		color[1] = 0;
	}*/

	//updte rotation
}
