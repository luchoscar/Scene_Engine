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
	void UpdateLightColor(float* lightCol, int lightId);
	void UpdateLightPosition(float* lightPos, int lightId);
	void UpdateIsEmissive(int emisive);
	void UpdateLightFallOffExp(float fallOffExp);
	CGparameter GetDecalMap() { return decalMap; }
	CGparameter GetNormalMap() { return normalMap; }

private:
	CGparameter decalMap,
				normalMap,
				lightColor[2],
				lightPossition[2],
				maxLights,
				isEmissive,
				lightFallOffExp;

	void BindSceneLisghtsNumber(int maxLights);
};