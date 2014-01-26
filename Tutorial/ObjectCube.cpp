#include "StdAfx.h"
#include "ObjectCube.h"
#include <math.h>
#include <iostream>
#include <string>
#include "Matrix3D.h"
//#include <GL/glut.h>

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
	vb = new float[72];

	//front face
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

	//back face
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

	//top face
	vb[24] = 0.5;
	vb[25] = 0.5;
	vb[26] = 0.5;

	vb[27] = 0.5;
	vb[28] = 0.5;
	vb[29] = -0.5;

	vb[30] = -0.5;
	vb[31] = 0.5;
	vb[32] = -0.5;

	vb[33] = -0.5;
	vb[34] = 0.5;
	vb[35] = 0.5;

	//bottom face
	vb[36] = -0.5;
	vb[37] = -0.5;
	vb[38] = 0.5;

	vb[39] = -0.5;
	vb[40] = -0.5;
	vb[41] = -0.5;

	vb[42] = 0.5;
	vb[43] = -0.5;
	vb[44] = -0.5;

	vb[45] = 0.5;
	vb[46] = -0.5;
	vb[47] = 0.5;

	//left face
	vb[48] = -0.5;
	vb[49] = 0.5;
	vb[50] = 0.5;

	vb[51] = -0.5;
	vb[52] = 0.5;
	vb[53] = -0.5;

	vb[54] = -0.5;
	vb[55] = -0.5;
	vb[56] = -0.5;

	vb[57] = -0.5;
	vb[58] = -0.5;
	vb[59] = 0.5;

	//right face
	vb[60] = 0.5;
	vb[61] = 0.5;
	vb[62] = 0.5;

	vb[63] = 0.5;
	vb[64] = -0.5;
	vb[65] = 0.5;

	vb[66] = 0.5;
	vb[67] = -0.5;
	vb[68] = -0.5;

	vb[69] = 0.5;
	vb[70] = 0.5;
	vb[71] = -0.5;

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
	cb = new float[24];
	for (int i = 0; i < 24; i += 3)
	{
		cb[i + 0] = color[0];
		cb[i + 1] = color[1];
		cb[i + 2] = color[2];
	}
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

void ObjectCube::DrawBuffers()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_INDEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vb);
	//glIndexPointer(GL_INT, 0, ib);

	glDrawArrays(GL_QUADS, 0, 72);

	//glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}