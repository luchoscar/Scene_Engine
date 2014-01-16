#pragma once

#include "VertexObject.h"

class PixelLightVS :
	public VertexObject
{
public:
	PixelLightVS();
	~PixelLightVS();

	void UpdateModelViewMatrix(float* MVP);
	void UpdateMatrixModelWorld(float* MVP);
	void UpdateMatrixViewProj(float* MVP);
	void UpdateLightPosition(float* lightPos);
	//void UpdateInverseModelViewMatrix(float* MVP);
	//void UpdateCameraPosition(float* camPos);

	virtual void LinkParameters();

protected:
	//CGprogram vertexProgram;

	CGparameter matrixModelWorld,
				matrixViewProj,
				modelViewProj,
				inverseModelToWorld,
				lightPosition,
				cameraPosition;
};

