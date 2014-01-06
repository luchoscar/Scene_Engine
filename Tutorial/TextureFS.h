#pragma once
#include "FragmentObject.h"
class TextureFS : public FragmentObject
{
public:
	TextureFS();
	virtual ~TextureFS();

	virtual void LinkParameters() { };

private:
	CGparameter decalMap;
};

