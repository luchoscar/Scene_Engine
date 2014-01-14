#pragma once
#include "SceneBase.h"
class PixelLightScene :
	public SceneBase
{
public:
	PixelLightScene();
	virtual ~PixelLightScene();

	virtual void Init() {};
	virtual void Draw() {};
	virtual void Update() {};

private:
};

