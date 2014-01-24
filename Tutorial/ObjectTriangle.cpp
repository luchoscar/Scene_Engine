#include "StdAfx.h"
#include "ObjectTriangle.h"
#include <math.h>
#include <GL/glut.h>

ObjectTriangle::ObjectTriangle() : BaseObject()
{
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;

	rotation[0] = 0.0;
	rotation[1] = 0.0;
	rotation[2] = 0.0;

	scale[0] = 1.0;
	scale[1] = 1.0;
	scale[2] = 1.0;

	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;

	Init();
}

ObjectTriangle::ObjectTriangle(float posX, float posY, float posZ, 
								float rotX, float rotY, float rotZ, 
								float sizeX, float sizeY, float sizeZ,
								float colorR, float colorG, float colorB) : BaseObject()
{
	position[0] = posX;
	position[1] = posY;
	position[2] = posZ;

	rotation[0] = rotX;
	rotation[1] = rotY;
	rotation[2] = rotZ;

	scale[0] = sizeX;
	scale[1] = sizeY;
	scale[2] = sizeZ;

	color[0] = colorR;
	color[1] = colorG;
	color[2] = colorB;
	
	Init();
}

void ObjectTriangle::Init()
{
	//vertex buffer
	vb = new float[9];
	vb[0] = -0.5;
	vb[1] =  0.5;
	vb[2] =  0.0;

	vb[3] =  0.5;
	vb[4] =  0.5;
	vb[5] =  0.0;

	vb[6] =  0.0;
	vb[7] = -0.5;
	vb[8] =  0.0;

	//index buffer
	ib = new int[3];
	ib[0] = 0;
	ib[1] = 1;
	ib[2] = 2;

	//color buffer
	cb = new float[9];
	cb[0] = color[0];
	cb[1] = color[1];
	cb[2] = color[2];

	cb[3] = color[0];
	cb[4] = color[1];
	cb[5] = color[2];

	cb[6] = color[0];
	cb[7] = color[1];
	cb[8] = color[2];
}

ObjectTriangle::~ObjectTriangle(void)
{
}

//calculate triangle based on XY-scale 
void ObjectTriangle::Draw()
{
	glBegin(GL_TRIANGLES);
		glColor3f(cb[0], cb[1], cb[2]);
		
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[0], vb[1], vb[2]);

		glColor3f(cb[3], cb[4], cb[5]);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(vb[3], vb[4], vb[5]);

		glColor3f(cb[6], cb[7], cb[8]);
		glTexCoord2f(1.0, 0.5); 
		glVertex3f(vb[6], vb[7], vb[8]);
	glEnd();
}

void ObjectTriangle::Update()
{

}

float* ObjectTriangle::GetVertexBuffer()
{
	return vb;
}

int* ObjectTriangle::GetIndexBuffer()
{
	return ib;
}

float* ObjectTriangle::GetColorBuffer()
{
	return cb;
}