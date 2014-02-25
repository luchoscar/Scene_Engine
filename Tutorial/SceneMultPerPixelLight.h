#pragma once
#include "SceneBase.h"
#include "ObjectCamera.h"
#include "MultPerPixelLightVS.h"
#include "MultPerPixelLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"

class SceneMultPerPixelLight :
	public SceneBase
{
public:
	SceneMultPerPixelLight();
	~SceneMultPerPixelLight();

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
	float* lightAngle;
	float* lightAngleDelta;
	float* lightRadMov;
	float lightFallOffExp;

	//camera variables
	ObjectCamera* cameraObject;
	float cameraPosAngle;
	float cameraPosAngleDelta;
	float cameraPosRadMov;
};

