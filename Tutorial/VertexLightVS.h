#pragma once

#include "VertexObject.h"

class VertexLightVS :
	public VertexObject
{
public:
	VertexLightVS();
	~VertexLightVS();

	void UpdateModelViewMatrix(float* MVP);
	void UpdateMatrixModelWorld(float* MVP);
	void UpdateMatrixViewProj(float* MVP);
	void UpdateLightPosition(float* lightPos);

	virtual void LinkParameters();

protected:
	CGparameter matrixModelWorld,
				matrixViewProj,
				modelViewProj,
				inverseModelToWorld,
				lightPosition, 
				cameraPosition;
};

