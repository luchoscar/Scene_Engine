#pragma once

#include "FragmentObject.h"

class PixelLightFS :
	public FragmentObject
{
public:
	PixelLightFS();
	~PixelLightFS();

	virtual void LinkParameters() {}

private:
	CGparameter decalMap,
				normalMap;
};

