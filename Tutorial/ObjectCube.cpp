#include "StdAfx.h"
#include "ObjectCube.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>

ObjectCube::ObjectCube() : BaseObject()
{
	position[0] = 0.0;
	position[1] = 0.0;
	position[2] = 0.0;

	rotation[0] = 0.0;
	rotation[1] = 0.0;
	rotation[2] = 0.0;

	scale[0] = 0.5;
	scale[1] = 0.5;
	scale[2] = 0.5;

	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;

	Init();
}


ObjectCube::ObjectCube(float posX, float posY, float posZ, 
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

void ObjectCube::Init()
{
	//vertex buffer - 8 vertices - x, y, z
	vb = new float[24];

	//front top left corner
	vb[0] = -0.5;
	vb[1] =  0.5;
	vb[2] =  0.5;

	//front bottom left corner
	vb[3] = -0.5;
	vb[4] = -0.5;
	vb[5] =  0.5;

	//front bottom right corner
	vb[6] =  0.5;
	vb[7] = -0.5;
	vb[8] =  0.5;

	//front top right corner
	vb[9]  =  0.5;
	vb[10] =  0.5;
	vb[11] =  0.5;

	//back top right corner
	vb[12] =  0.5;
	vb[13] =  0.5;
	vb[14] = -0.5;

	//back bottom right corner
	vb[15] =  0.5;
	vb[16] = -0.5;
	vb[17] = -0.5;

	//back bottom left corner
	vb[18] = -0.5;
	vb[19] = -0.5;
	vb[20] = -0.5;

	//back top left corner
	vb[21] = -0.5;
	vb[22] =  0.5;
	vb[23] = -0.5;

	//index buffer
	ib = new float[3];

	//color buffer
	cb = new float[18];

	//front
	cb[0] = color[0];
	cb[1] = color[1];
	cb[2] = color[2];

	//back
	cb[3] = 0.0;
	cb[4] = color[1];
	cb[5] = color[2];

	//top
	cb[6] = color[0];
	cb[7] = 0.0;
	cb[8] = color[2];

	//bottom
	cb[9] = color[0];
	cb[10] = color[1];
	cb[11] = 0.0;

	//right
	cb[12] = color[0];
	cb[13] = 0.0;
	cb[14] = 0.0;

	//left
	cb[15] = 0.0;
	cb[16] = color[1];
	cb[17] = 0.0;
}

ObjectCube::~ObjectCube(void)
{
}

//calculate triangle based on XY-scale 
void ObjectCube::Draw()
{
	//front face
	//glBegin(GL_QUADS);
	glBegin(GL_TRIANGLES);
		glColor3f(cb[0], cb[1], cb[2]);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[0], vb[1], vb[2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(vb[3], vb[4], vb[5]);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(vb[6], vb[7], vb[8]);
	glEnd(); 
	glBegin(GL_TRIANGLES);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(vb[6], vb[7], vb[8]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(vb[9], vb[10], vb[11]);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[0], vb[1], vb[2]);
	glEnd();

	//back face
	glBegin(GL_QUADS);
		glColor3f(cb[3], cb[4], cb[5]);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[12], vb[13], vb[14]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(vb[15], vb[16], vb[17]);
		glTexCoord2f(1.0, 1.0); 
		glVertex3f(vb[18], vb[19], vb[20]);
		glTexCoord2f(1.0, 0.0); 
		glVertex3f(vb[21], vb[22], vb[23]);
	glEnd();

	//top face
	glBegin(GL_QUADS);
		glColor3f(cb[6], cb[7], cb[8]);
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(vb[9], vb[10], vb[11]);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(vb[12], vb[13], vb[14]);
		glTexCoord2f(1.0, 1.0); 
		glVertex3f(vb[21], vb[22], vb[23]);
		glTexCoord2f(1.0, 0.0); 
		glVertex3f(vb[0], vb[1], vb[2]);
	glEnd();

	//bottom face
	glBegin(GL_QUADS);
		glColor3f(cb[9], cb[10], cb[11]);
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(vb[3], vb[4], vb[5]);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(vb[18], vb[19], vb[20]);
		glTexCoord2f(1.0, 1.0); 
		glVertex3f(vb[15], vb[16], vb[17]);
		glTexCoord2f(1.0, 0.0); 
		glVertex3f(vb[6], vb[7], vb[8]);
	glEnd();

	//right face
	glBegin(GL_QUADS);
		glColor3f(cb[12], cb[13], cb[14]);
		glVertex3f(vb[12], vb[13], vb[14]);
		glVertex3f(vb[9], vb[10], vb[11]);
		glVertex3f(vb[6], vb[7], vb[8]);
		glVertex3f(vb[15], vb[16], vb[17]);
	glEnd();

	//left face
	glBegin(GL_QUADS);
		glColor3f(cb[15], cb[16], cb[17]);
		glVertex3f(vb[0], vb[1], vb[2]);
		glVertex3f(vb[21], vb[22], vb[23]);
		glVertex3f(vb[18], vb[19], vb[20]);
		glVertex3f(vb[3], vb[4], vb[5]);
	glEnd();
}

void ObjectCube::Update()
{
	//rotation[0] += 25.0 * deltaTime;
	//rotation[0] += 0.125;
}

float* ObjectCube::GetVertexBuffer()
{
	return vb;
}

float* ObjectCube::GetIndexBuffer()
{
	return ib;
}

float* ObjectCube::GetColorBuffer()
{
	return cb;
}
