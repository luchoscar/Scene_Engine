#pragma once
#include "VertexObject.h"

class SimpleVS : public VertexObject
{
public:
	SimpleVS();
	~SimpleVS();

	void UpdateModelViewMatrix(float* MVP);
	CGparameter GetModelViewProjMatrix() { return vertexParam_modelViewProj; };

	virtual void LinkParameters();
	virtual void UpdateParameters();

private:
	CGparameter vertexParam_modelViewProj;
};

