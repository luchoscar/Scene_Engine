#pragma once

#include "SceneBase.h"
#include "VertexLightVS.h"
#include "VertexLightFS.h"
#include "SimpleVS.h"
#include "SimpleFS.h"

class PixelVertexScene :
	public SceneBase
{
public:
	PixelVertexScene();
	virtual ~PixelVertexScene();

	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	VertexLightVS vertexLightVS;
	VertexLightFS vertexLightFS;
};

