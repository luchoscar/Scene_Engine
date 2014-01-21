#include "StdAfx.h"
#include "ObjectCube.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include "Matrix3D.h"

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
	ib = new int[24];
	
	//front face
	ib[0] = 0;
	ib[1] = 1;
	ib[2] = 2;
	ib[3] = 3;

	//back face
	ib[4] = 4;
	ib[5] = 5;
	ib[6] = 6;
	ib[7] = 7;

	//top face
	ib[8] = 0;
	ib[9] = 3;
	ib[10] = 4;
	ib[11] = 7;

	//bottom face
	ib[12] = 1;
	ib[13] = 6;
	ib[14] = 5;
	ib[15] = 2;

	//left face
	ib[16] = 0;
	ib[17] = 7;
	ib[18] = 6;
	ib[19] = 1;

	//right face
	ib[20] = 3;
	ib[21] = 2;
	ib[22] = 5;
	ib[23] = 4;

	//normal buffer
	nb = new float[18];
	float normal[3];

	//front face
	Matrix3D::CalculateNormal(vb[6], vb[7], vb[8],
								vb[3], vb[4], vb[5],
								vb[0], vb[1], vb[2],
								normal);
	nb[0] = normal[0];
	nb[1] = normal[1];
	nb[2] = normal[2];

	//back face
	Matrix3D::CalculateNormal(vb[18], vb[19], vb[20],
								vb[15], vb[16], vb[17],
								vb[12], vb[13], vb[14],
								normal);
	nb[3] = normal[0];
	nb[4] = normal[1];
	nb[5] = normal[2];

	//top face
	Matrix3D::CalculateNormal(vb[21], vb[22], vb[23],
								vb[12], vb[13], vb[14],
								vb[9], vb[10], vb[11],
								normal);
	nb[6] = normal[0];
	nb[7] = normal[1];
	nb[8] = normal[2];

	//bottom face
	Matrix3D::CalculateNormal(vb[15], vb[16], vb[17],
								vb[18], vb[19], vb[20],
								vb[3], vb[4], vb[5],
								normal);
	nb[9] = normal[0];
	nb[10] = normal[1];
	nb[11] = normal[2];

	//left face
	Matrix3D::CalculateNormal(vb[18], vb[19], vb[20],
								vb[21], vb[22], vb[23],
								vb[0], vb[1], vb[2],
								normal);
	nb[12] = normal[0];
	nb[13] = normal[1];
	nb[14] = normal[2];

	//right face
	Matrix3D::CalculateNormal(vb[6], vb[7], vb[8],
								vb[9], vb[10], vb[11],
								vb[12], vb[13], vb[14],
								normal);
	nb[15] = normal[0];
	nb[16] = normal[1];
	nb[17] = normal[2];

	//color buffer
	cb = new float[32];
	for (int i = 0; i < 32; i += 4)
	{
		cb[i + 0] = color[0];
		cb[i + 1] = color[1];
		cb[i + 2] = color[2];
		cb[i + 3] = 1.0f;
	}

	//glGenBuffers(1, vb);

	//glBindBuffer(GL_ARRAY_BUFFER, vb);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vb), vb, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ObjectCube::~ObjectCube(void)
{
}

//calculate triangle based on XY-scale 
void ObjectCube::Draw()
{
	float normal[3];
	//front face
	Matrix3D::CalculateNormal(vb[6], vb[7], vb[8],
								vb[3], vb[4], vb[5], 
								vb[0], vb[1], vb[2], 
								normal);
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[0], vb[1], vb[2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(vb[3], vb[4], vb[5]);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(vb[6], vb[7], vb[8]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(vb[9], vb[10], vb[11]);
	glEnd();

	//back face
	Matrix3D::CalculateNormal(vb[18], vb[19], vb[20],
								vb[15], vb[16], vb[17],
								vb[12], vb[13], vb[14], 
								normal); 
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
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
	Matrix3D::CalculateNormal(vb[21], vb[22], vb[23], 
								vb[12], vb[13], vb[14],
								vb[9], vb[10], vb[11],
								normal);
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
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
	Matrix3D::CalculateNormal(vb[15], vb[16], vb[17], 
								vb[18], vb[19], vb[20],
								vb[3], vb[4], vb[5],
								normal);
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
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
	Matrix3D::CalculateNormal(vb[6], vb[7], vb[8],
								vb[9], vb[10], vb[11],
								vb[12], vb[13], vb[14], 
								normal);
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(vb[12], vb[13], vb[14]);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(vb[9], vb[10], vb[11]);
		glTexCoord2f(1.0, 1.0); 
		glVertex3f(vb[6], vb[7], vb[8]);
		glTexCoord2f(1.0, 0.0); 
		glVertex3f(vb[15], vb[16], vb[17]);
	glEnd();

	//left face
	Matrix3D::CalculateNormal(vb[18], vb[19], vb[20], 
								vb[21], vb[22], vb[23],
								vb[0], vb[1], vb[2],
								normal);
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(normal);
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(vb[0], vb[1], vb[2]);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(vb[21], vb[22], vb[23]);
		glTexCoord2f(1.0, 1.0); 
		glVertex3f(vb[18], vb[19], vb[20]);
		glTexCoord2f(1.0, 0.0); 
		glVertex3f(vb[3], vb[4], vb[5]);
	glEnd();
}

void ObjectCube::Update()
{
}

float* ObjectCube::GetVertexBuffer()
{
	return vb;
}

int* ObjectCube::GetIndexBuffer()
{
	return ib;
}

float* ObjectCube::GetColorBuffer()
{
	return cb;
}
