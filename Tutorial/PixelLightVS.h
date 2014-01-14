#pragma once

#include "VertexObject.h"

class PixelLightVS :
	public VertexObject
{
public:
	PixelLightVS();
	~PixelLightVS();

	void UpdateModelViewMatrix(float* MVP);
	void UpdateInverseModelViewMatrix(float* MVP);
	void UpdateLightPosition(float* lightPos);
	void UpdateCameraPosition(float* camPos);

	virtual void LinkParameters();

protected:
	CGprogram vertexProgram;

	CGparameter modelViewProj,
				inverseModelToWorld,
				lightPosition,
				cameraPosition;
};

