#pragma once
#include "VertexObject.h"

class SimpleVS : public VertexObject
{
public:
	SimpleVS();
	~SimpleVS();

	virtual void UpdateParameters() {};

private:
	CGparameter vertexParam_modelViewProj;
};

