#pragma once
#include "FragmentObject.h"
class TextureFS : public FragmentObject
{
public:
	TextureFS();
	virtual ~TextureFS();

	void LoadTexture();
	void SetTextureParameter(GLuint textureParam);
	
	virtual void LinkParameters();

private:
	CGparameter decalMap;
};

