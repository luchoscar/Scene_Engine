#pragma once
#include "FragmentObject.h"
class TextureFS : public FragmentObject
{
public:
	TextureFS();
	virtual ~TextureFS();

	void LoadTexture();

	virtual void LinkParameters();

private:
	CGparameter decalMap;
};

