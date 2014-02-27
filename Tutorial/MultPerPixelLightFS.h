#pragma once
#include "FragmentObject.h"

class MultPerPixelLightFS :
	public FragmentObject
{
public:
	MultPerPixelLightFS();
	MultPerPixelLightFS(int In_lightsNum);
	~MultPerPixelLightFS();

	virtual void LinkParameters();

	void SetDecalMap(GLuint textureParam);
	void SetNormalMap(GLuint textureParam);
	void UpdateCameraPosition(float* camPos);
	void UpdateLightPosition(float* lightPos, int lightId); 
	void UpdateLightColor(float* lightCol, int lightId);
	void UpdateLightFallOffExp(float fallOffExp);
	void UpdateMatrixModelWorld(float* matModWorld);
	void UpdateSpeculatPower(float specPower);

	CGparameter GetDecalMap() { return decalMap; }
	CGparameter GetNormalMap() { return normalMap; }

private:
	CGparameter decalMap,
				normalMap,
				cameraPosition,
				lightPossition[7],
				lightColor[7],
				lightFallOffExp,
				matrixModelWorld,
				specularPower;
};