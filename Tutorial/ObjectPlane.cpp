#include "stdafx.h"
#include "ObjectPlane.h"


ObjectPlane::ObjectPlane()
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

ObjectPlane::ObjectPlane(float posX, float posY, float posZ,
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
ObjectPlane::~ObjectPlane()
{
}

void ObjectPlane::Init()
{
	vb = new float[12];
	vb[0]  = -0.5f;
	vb[1]  =  0.0f;
	vb[2]  =  0.5f;

	vb[3]  =  0.5f;
	vb[4]  =  0.0f;
	vb[5]  =  0.5f;

	vb[6]  =  0.5f;
	vb[7]  =  0.0f;
	vb[8]  = -0.5f;

	vb[9]  = -0.5f;
	vb[10] = 0.0f;
	vb[11] = -0.5f;

	nb = new float[3];
	nb[0] = 0.0f;
	nb[1] = 1.0f;
	nb[2] = 0.0f;

	cb = new float[3];
	cb[0] = color[0];
	cb[1] = color[1];
	cb[2] = color[2];
}

float* ObjectPlane::GetVertexBuffer()
{
	return vb;
}

int* ObjectPlane::GetIndexBuffer()
{
	return ib;
}

float* ObjectPlane::GetColorBuffer()
{
	return cb;
}

void ObjectPlane::Draw()
{
	glBegin(GL_QUADS);
		glColor3f(cb[0], cb[1], cb[2]);
		glNormal3fv(nb);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(vb[0], vb[1], vb[2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(vb[3], vb[4], vb[5]);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(vb[6], vb[7], vb[8]);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(vb[9], vb[10], vb[11]);
	glEnd();
}

void ObjectPlane::DrawBuffers()
{

}

void ObjectPlane::Update()
{

}