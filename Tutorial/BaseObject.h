/****************************************************
 * Abstract base class for all objects in a scene	*
 ****************************************************/

#pragma once

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	float* GetPosition();
	float* GetRotation();
	float* GetScale();

	void TranslateOnAxis(float xPos, float yPos, float zPos);
	void RotationAroundAxis(float xRot, float yRot, float zRot);

	virtual void Init() = 0;
	virtual float* GetVertexBuffer() = 0;
	virtual float* GetIndexBuffer() = 0;
	virtual float* GetColorBuffer() = 0;

	virtual void Draw() = 0;
	virtual void Update() = 0;

protected:
	float color[3];
	float position[3];
	float rotation[3];
	float scale[3];

	float *ib;	//index buffer
	float *vb;	//vertex buffer
	float *nb;	//normal buffer
	float *cb;	//color buffer
};
