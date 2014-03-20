#pragma once

#include "SceneBase.h"
#include "ObjectCamera.h"
#include "MultPerPixelLightVS.h"
#include "MultPerPixelLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"

class SceneParticleEffect :
	public SceneBase
{
public:
	SceneParticleEffect();
	~SceneParticleEffect();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	MultPerPixelLightVS pixelLightVS;
	MultPerPixelLightFS pixelLightFS;
	SimpleFS simpleFS;
	SimpleVS simpleVS;

	//light variables
	int maxLights;
	float lightFallOffExp;
	float specularPower;

	//camera variables
	ObjectCamera* cameraObject;
};

