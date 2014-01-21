#include "StdAfx.h"
#include "Engine.h"
//#include <GL/glew.h>
#include <GL/glut.h>
#include "TextureColorScene.h"
#include <iostream>
#include "PixelVertexScene.h"

//static variables
Matrix3D Engine::perspective;
float Engine::deltaTime;
float Engine::previousTime;

SceneBase* scene;

Engine::Engine()
{
	//scene = new TextureColorScene();
	scene = new PixelVertexScene();
	
	previousTime = 0.0;
}

Engine::~Engine()
{
	delete scene;
}

void Engine::Init(int argc, char* argv[])
{
	//Set up window
	glutInitWindowSize(450, 350);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST); 

	glutInit(&argc, argv);
	glutCreateWindow("Scene Engine");
	//glewInit();

	//Set up callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutIdleFunc(Update);
	glutKeyboardFunc(Keyboard);

	scene->Init();
}

void Engine::Run()
{
	glutMainLoop();
}

void Engine::Display()
{
	scene->Draw();
	glutSwapBuffers();
}

void Engine::Update()
{
	// calculate fps & frame time
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	Engine::deltaTime = (currentTime - Engine::previousTime) * 0.001;
	Engine::previousTime = currentTime;
	float fps = 1 / (Engine::deltaTime);
	
	std::cout << "Fame Time (delta Time = " << Engine::deltaTime << " seconds " << std::endl;
	std::cout << "Engine fps = " << fps << std::endl;
	
	//run scene update
	scene->Update();

	//update draw buffers
	glutPostRedisplay();
}

void Engine::Keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'w':
		glutPostRedisplay();
		break;
	case 'a':
		break;
	case 's':
		break;
	case 'd':
		break;
	case ' ':
		{
		}
		break;
	case 27:
		exit(1);
		break;
	}
}

void Engine::Resize(int width, int height)
{
	float aspectRatio = (float)width / (float)height;
	Matrix3D::BuildPerspectiveMatrix(65, aspectRatio, 1.0, 1000.0, Engine::perspective);

	glViewport(0, 0, width, height);
}




