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
	void UpdateMatrixMVP(float* MWVP);

	virtual void LinkParameters();

protected:
	CGparameter tangent,
				bitangent,
				matrixMVP;
};

