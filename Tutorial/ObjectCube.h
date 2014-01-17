#pragma once
#include "baseobject.h"
class ObjectCube : public BaseObject
{
public:
	ObjectCube();
	ObjectCube(float posX, float posY, float posZ, 
								float rotX, float rotY, float rotZ, 
								float sizeX, float sizeY, float sizeZ,
								float colorR, float colorG, float colorB);
	virtual ~ObjectCube();

	virtual void Init();
	virtual float* GetVertexBuffer();
	virtual int* GetIndexBuffer();
	virtual float* GetColorBuffer();

	virtual void Draw();
	virtual void Update();
	
protected:
};

