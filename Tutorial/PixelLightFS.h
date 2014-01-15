#pragma once

#include "FragmentObject.h"

class PixelLightFS :
	public FragmentObject
{
public:
	PixelLightFS();
	~PixelLightFS();

	virtual void LinkParameters();
	void SetDecalMap(GLuint textureParam);
	void SetNormalMap(GLuint textureParam);

private:
	CGparameter decalMap,
				normalMap;
};

