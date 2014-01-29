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

private:
	CGparameter decalMap,
		normalMap,
		lightColor;
};

