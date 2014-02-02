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
	void UpdateMatrixModelWorld(float* World);
	void UpdateMatrixViewProj(float* ViewProj);
	void UpdateLightPosition(float* lightPos);
	void UpdateCameraPosition(float* camPos);

	virtual void LinkParameters();

protected:
	CGparameter tangent,
				bitangent,
				matrixModelWorld,
				matrixViewProj,
				lightPosition,
				cameraPosition;
};

