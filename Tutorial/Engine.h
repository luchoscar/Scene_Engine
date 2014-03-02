/****************************************************
 * Class to control windows events and game loop	*
 ****************************************************/

#pragma once

#include "Matrix3D.h"
#include "SceneBase.h"
#include <vector>

class Engine
{
public:
	static float deltaTime;
	
	Engine();
	~Engine();

	void Init(int argc, char* argv[]);
	void Run();

	/* Forward declared GLUT callbacks registered by main. */
	static void Display();
	static void Update();
	static void Keyboard(unsigned char c, int x, int y);
	static void Resize(int width, int height);
	static Matrix3D perspective;

private:
	//static SceneBase *scene;
	static float previousTime;	
	//vector<SceneBase*> scenesList;
};
