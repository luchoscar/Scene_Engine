#include "stdafx.h"
#include "ObjectCamera.h"


ObjectCamera::ObjectCamera()
{
}

ObjectCamera::ObjectCamera(float posX, float posY, float posZ,
							float upX, float upY, float upZ,
							float lookAtX, float lookAtY, float lookAtZ)
{
	position[0] = posX;
	position[1] = posY;
	position[2] = posZ;

	lookAt[0] = lookAtX;
	lookAt[1] = lookAtY;
	lookAt[2] = lookAtZ;

	upVector[0] = upX;
	upVector[1] = upY;
	upVector[2] = upZ;

	cameraUpdated = true;	//setting to true as camera has to be updated in order to be initialized
}

ObjectCamera::~ObjectCamera()
{
}

void ObjectCamera::Init()
{
	CalculateViewMatrix();
}

//calculate ViewProjection matrix
void ObjectCamera::CalculateViewMatrix()
{
	if (!cameraUpdated) return;

	Matrix3D::BuildLookAtMatrix(position[0], position[1], position[2],
								lookAt[0], lookAt[1], lookAt[2],	//point that camera looks at
								upVector[0], upVector[1], upVector[2],	//camera up vector
								viewMatrix);

	cameraUpdated = false;
}

void ObjectCamera::SetPosition(float xPos, float yPos, float zPos)
{
	cameraUpdated = true;

	BaseObject::SetPosition(xPos, yPos, zPos);
}

void ObjectCamera::SetLookAtVector(float xLooAt, float yLooAt, float zLooAt)
{
	cameraUpdated = true;

	lookAt[0] = xLooAt;
	lookAt[1] = yLooAt;
	lookAt[2] = zLooAt;
}