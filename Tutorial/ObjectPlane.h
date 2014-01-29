#pragma once
#include "BaseObject.h"
class ObjectPlane :
	public BaseObject
{
public:
	ObjectPlane();
	ObjectPlane(float posX, float posY, float posZ,
				float rotX, float rotY, float rotZ,
				float sizeX, float sizeY, float sizeZ,
				float colorR, float colorG, float colorB);
	~ObjectPlane();

	virtual void Init();
	virtual float* GetVertexBuffer();
	virtual int* GetIndexBuffer();
	virtual float* GetColorBuffer();

	virtual void Draw();
	virtual void DrawBuffers();
	virtual void Update();
protected:
};

