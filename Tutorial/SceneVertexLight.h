#pragma once

#include "SceneBase.h"
#include "VertexLightVS.h"
#include "VertexLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"

class SceneVertexLight :
	public SceneBase
{
public:
	SceneVertexLight();
	virtual ~SceneVertexLight();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	VertexLightVS vertexLightVS;
	VertexLightFS vertexLightFS;
	SimpleVS simpleVS;
	SimpleFS simpleFS;

	//light variables
	float lightPos[3];
	float lightRad;
	float angleLightRot;
	float anfleDelta;
};

