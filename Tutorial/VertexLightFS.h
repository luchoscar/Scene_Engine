#pragma once

#include "FragmentObject.h"

class VertexLightFS :
	public FragmentObject
{
public:
	VertexLightFS();
	~VertexLightFS();

	virtual void LinkParameters();
	void SetDecalMap(GLuint textureParam);
	void SetNormalMap(GLuint textureParam);
	void UpdateLightColor(float* lightCol);

private:
	CGparameter decalMap,
				normalMap,
				lightColor;
};

