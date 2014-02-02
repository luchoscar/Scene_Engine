#pragma once
#include "FragmentObject.h"
class PerPixelLightFS :
	public FragmentObject
{
public:
	PerPixelLightFS();
	~PerPixelLightFS();

	virtual void LinkParameters();
	void SetDecalMap(GLuint textureParam);
	void SetNormalMap(GLuint textureParam);
	void UpdateLightColor(float* lightCol);
	CGparameter GetDecalMap() { return decalMap; }
	CGparameter GetNormalMap() { return normalMap; }

private:
	CGparameter decalMap,
				normalMap,
				lightColor;
};

