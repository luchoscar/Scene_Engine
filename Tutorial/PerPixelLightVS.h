#pragma once
#include "VertexObject.h"

class PerPixelLightVS :
	public VertexObject
{
public:
	PerPixelLightVS();
	~PerPixelLightVS();

	void UpdateTangent(float* tan);
	void UpdateBitangent(float* bitan);
	void UpdateModelViewMatrix(float* MVP);
	void UpdateMatrixModelWorld(float* MVP);
	void UpdateMatrixViewProj(float* MVP);
	void UpdateLightPosition(float* lightPos);

	virtual void LinkParameters();

protected:
	CGparameter tangent,
		bitangent,
		matrixModelWorld,
		matrixViewProj,
		modelViewProj,
		lightPosition;
};

