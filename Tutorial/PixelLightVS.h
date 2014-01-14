#pragma once

#include "VertexObject.h"

class PixelLightVS :
	public VertexObject
{
public:
	PixelLightVS();
	~PixelLightVS();

	virtual void LinkParameters() = 0;
protected:
	CGprogram vertexProgram, lightPosition, cameraPosition;

	CGparameter vertexParam_modelViewProj;
};

