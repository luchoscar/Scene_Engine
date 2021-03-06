#pragma once
#include "SceneBase.h"
#include "PerPixelLightVS.h"
#include "PerPixelLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"
#include "ObjectCamera.h"

class ScenePerPixelLight :
	public SceneBase
{
public:
	ScenePerPixelLight();
	virtual ~ScenePerPixelLight();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	PerPixelLightVS pixelLightVS;
	PerPixelLightFS pixelLightFS;
	SimpleFS simpleFS;
	SimpleVS simpleVS;

	//light variables
	float lightPos[3];
	float lightColor[3];
	float lightAngle;
	float lightAngleDelta;
	float lightRadMov;
	float lightFallOffExp;

	//camera variables
	ObjectCamera* cameraObject;
	float cameraPosAngle;
	float cameraPosAngleDelta;
	float cameraPosRadMov;
};