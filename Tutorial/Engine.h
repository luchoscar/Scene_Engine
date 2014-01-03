/****************************************************
 * Class to control windows events and game loop	*
 ****************************************************/

#pragma once
#include "Matrix3D.h"

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

protected:
	static float previousTime;	//time for previous frame
};
