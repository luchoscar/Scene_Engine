#include "StdAfx.h"
#include <CG\cg.h>
#include "Engine.h"
#include <iostream>
#include "SceneTextureColor.h"
#include "SceneVertexLight.h"
#include "SceneBuffers.h"
#include "ScenePerPixelLight.h"
#include "SceneMultPerPixelLight.h"
#include "SceneParticleEffect.h"

//static variables
Matrix3D Engine::perspective;
float Engine::deltaTime;
float Engine::previousTime;
//SceneBase* scene;
SceneBase* Engine::scene;

Engine::Engine()
{
	scenesList.push_back(new SceneTextureColor());
	scenesList.push_back(new SceneVertexLight());
	scenesList.push_back(new SceneBuffers());
	scenesList.push_back(new ScenePerPixelLight());
	scenesList.push_back(new SceneMultPerPixelLight());
	scenesList.push_back(new SceneParticleEffect());

	unsigned int sceneToLoad = scenesList.size() - 1;
	Engine::scene = scenesList[sceneToLoad];

	previousTime = 0.0;
}

Engine::~Engine()
{
	delete scene;

	for (unsigned int i = 0; i < scenesList.size(); i++)
	{
		delete scenesList[i];
	}

	scenesList.clear();
}

void Engine::Init(int argc, char* argv[])
{
	//Set up window
	glutInitWindowSize(450, 350);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 

	glutInit(&argc, argv);
	glutCreateWindow("Scene Engine");

	//Set up callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutIdleFunc(Update);
	glutKeyboardFunc(Keyboard);

	/* Initialize OpenGL entry points. */
	if (glewInit() != GLEW_OK || !GLEW_VERSION_1_3 || !GLEW_EXT_texture_compression_s3tc) {
		fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 1.3 and GL_EXT_texture_compression_s3tc required.\n", "Scene Engine");
		exit(1);
	}

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




