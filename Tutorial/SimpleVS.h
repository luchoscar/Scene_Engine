#pragma once
#include "VertexObject.h"

class SimpleVS : public VertexObject
{
public:
	SimpleVS();
	~SimpleVS();

	void UpdateModelViewMatrix(float* MVP);
	
	virtual void LinkParameters();

private:
	CGparameter modelViewProj;
};

