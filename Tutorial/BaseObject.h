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

	virtual void Draw() = 0;
	virtual void Update() = 0;

protected:
	float color[3];
	float position[3];
	float rotation[3];
	float scale[3];
};
