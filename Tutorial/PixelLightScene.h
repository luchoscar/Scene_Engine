#pragma once

#include "SceneBase.h"
#include "PixelLightVS.h"
#include "PixelLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"

class PixelLightScene :
	public SceneBase
{
public:
	PixelLightScene();
	virtual ~PixelLightScene();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	PixelLightVS pixelLightVS;
	PixelLightFS pixelLightFS;

	//SimpleVS pixelLightVS;
	//SimpleFS pixelLightFS;
};

