#include "StdAfx.h"
#include "ObjectCube.h"
//#include <GL/glut.h>
#include <math.h>

ObjectCube::ObjectCube() : BaseObject()
{
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;

	position[0] = 0;
	position[1] = 0;

	rotation = 0;

	scale = 1.0;
}

ObjectCube::ObjectCube(float x, float y, float size) : BaseObject()
{
	color[0] = 0;
	color[1] = 1;
	color[2] = 0;

	position[0] = x;
	position[1] = y;

	rotation = 0;

	scale = size * 0.5f;
}

ObjectCube::~ObjectCube(void)
{
}

void ObjectCube::Draw()
{
	//adjust rotation for each vertex
	//multiply by sin,cos , or something else

	//front face
	glBegin(GL_QUADS);
		glColor3f(color[0],color[1],color[2]);
		glVertex3f(position[0] + scale, position[1] + scale, position[3] + scale);
		glVertex3f(position[0] - scale, position[1] + scale, position[3] + scale);
		glVertex3f(position[0] - scale, position[1] - scale, position[3] + scale);
		glVertex3f(position[0] + scale, position[1] - scale, position[3] + scale);
	glEnd();
}

void ObjectCube::Update()
{
	color[1] += .01;
	if (color[1] > 1.0)
	{
		color[1] = 0;
	}

	//updte rotation
}
