#pragma once

#include "OpenGLRenderer.h"
#include "BaseObject.h"
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include "Engine.h"
#include "Matrix3D.h"

using namespace std; 

class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;

protected:
	//List holding all objects in scene
	vector<BaseObject*> list;

	OpenGLRenderer rendererGL;
	TextureManager textureManager;
};

