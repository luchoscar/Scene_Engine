/********************************
 * Holds game logic and objects	*
 ********************************/

#pragma once

#include "SimpleVS.h"
#include "SimpleFS.h"
#include "TextureFS.h"
#include "SceneBase.h"

using namespace std;

class SceneTextureColor : public SceneBase
{
public:
	SceneTextureColor();
	virtual ~SceneTextureColor();
	
	virtual void Init();
	virtual void Draw();
	virtual void Update();

private:
	SimpleVS simpleVS;
	SimpleFS simpleFS;
	TextureFS textureFS;
};
