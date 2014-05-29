#pragma once
#include "GeometryObject.h"

class BillboardGS :
	public GeometryObject
{
public:
	BillboardGS();
	~BillboardGS();

	void UpdateCameraPosition(float* camPos);
	void UpdateBillboardSize(float size);
	void UpdateMatrixMVP(float* MWVP);

	virtual void LinkParameters();

private:
	CGparameter cameraPosition,
				billboardSize,
				matrixMVP;
};

