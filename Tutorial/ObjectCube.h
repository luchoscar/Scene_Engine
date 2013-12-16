#pragma once
#include "BaseObject.h"
#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>

class ObjectCube : public BaseObject
{
public:
	ObjectCube();
	ObjectCube(float x, float y, float size);
	virtual ~ObjectCube();
	
	virtual void Draw();
	virtual void Update();

protected:
	float color[3];
	float position[2];
	float rotation;
	float scale;
};
