#pragma once
#include "BaseObject.h"

class ObjectTriangle : public BaseObject
{
public:
	ObjectTriangle();
	ObjectTriangle(float x, float y, float size);
	virtual ~ObjectTriangle();

	virtual void Draw();
	virtual void Update();

protected:
	/*float color[3];
	float position[2];
	float rotation;
	float scale;*/
};
