#pragma once
#include "VertexObject.h"

class MultPerPixelLightVS :
	public VertexObject
{
public:
	MultPerPixelLightVS();
	~MultPerPixelLightVS();

	void UpdateTangent(float* tan);
	void UpdateBitangent(float* bitan);
	void UpdateMatrixModelWorld(float* World);
	void UpdateMatrixViewProj(float* ViewProj);
	void UpdateCameraPosition(float* camPos);

	virtual void LinkParameters();

protected:
	CGparameter tangent,
				bitangent,
				cameraPosition,
				matrixModelWorld,
				matrixViewProj;
};

