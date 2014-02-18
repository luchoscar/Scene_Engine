#pragma once
#include "BaseObject.h"
#include "Matrix3D.h"

class ObjectCamera :
	public BaseObject
{
public:
	ObjectCamera();
	ObjectCamera(float posX, float posY, float posZ,
					float upX, float upY, float upZ,
					float lookAtX, float lookAtY, float lookAtZ);
	~ObjectCamera();

	void CalculateViewMatrix();	
	Matrix3D GetViewMatrix()	{ return viewMatrix; }
	void SetLookAtVector(float xLooAt, float yLooAt, float zLooAt);
	float* GetLookAtVector() { return lookAt; }
	
	virtual void Init();
	virtual void SetPosition(float xPos, float yPos, float zPos);
	virtual void Draw() {};
	virtual void DrawBuffers() {};
	virtual void Update() {};

	//not needed by the camera
	virtual float* GetVertexBuffer() { return NULL; };
	virtual int* GetIndexBuffer() { return NULL; };
	virtual float* GetColorBuffer() { return NULL; };

private:
	Matrix3D viewMatrix;
	float lookAt[3];
	float upVector[3];
	bool cameraUpdated;	//flag indicating wheather camera values have changed
};

