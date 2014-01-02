/****************************************************************************
 * Scene to control game logic - evenually to be made into a hierarchy		*
 * in order to implement a Vector<SceneBase> from Engine.cpp				*
 * Logic to create, enable and disable VS & FS to be moved to its own		*
 * hierarchy system															*
 * Camera to be set as its own derviced class from BaseObject				*
 ****************************************************************************/

#include "StdAfx.h"
#include "Scene.h"
#include "ObjectTriangle.h"
#include "ObjectCube.h"
#include "Matrix3D.h"
#include "Engine.h"
#include <iostream>

const char *myVertexProgramFileName = "vertex_shader.cg",
			*myVertexProgramName = "VS_program",
			*myFragmentProgramFileName = "fragment_shader.cg",
			*myFragmentProgramName = "FS_program";

float Scene::deltaTime = 0.0f;

Scene::Scene(void)
{

}

Scene::~Scene(void)
{
	//Delete all objects in list
	for (unsigned int i=0; i<list.size(); i++)
	{
		delete list[i];
	}

	list.clear();
}

//initializing scene
void Scene::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	//creating VS program
	simpleVS.CreateProgram(myVertexProgramFileName, myVertexProgramName);

	//Loads the vertex program into memory
	rendererGL.LoadProgram(simpleVS.GetProgram());
	
	//binding VS shader variables
	simpleVS.LinkParameters();

	//creating FS program
	simpleFS.CreateProgram(myFragmentProgramFileName, myFragmentProgramName);

	//Loads the fragment program into memory
	rendererGL.LoadProgram(simpleFS.GetProgram());

	//adding default scene objects
	//camera object should be added in the constructor and as the first object of the list for easy access
	list.push_back(new ObjectTriangle());
	list.push_back(new ObjectTriangle(0.5, 1.75, 0.0, 0.0, 0.0, 30.0, 1.5, 1.5, 1.5, 1.0, 0.5, 0.25));
	list.push_back(new ObjectCube(-1.5, 1.5, -2.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
	list.push_back(new ObjectCube(1.5, -0.70, 0.0, 25.0, 30.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
}

void Scene::Draw()
{
	rendererGL.ClearGLFlags();

	//bind CG program
	rendererGL.BindProgram(simpleVS.GetProgram());

	//Enable VS & FS profiles
	rendererGL.EnableProfile(rendererGL.GetVertexProfile());
	rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

	Matrix3D MVP, viewMatrix, modelViewMatrix, modelMatrix, translateMatrix, rotationMatrix;
	
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, 5,		//camera position
								  0.0, 0.0, 0.0,	//point that camera looks at
								  0.0, 1.0, 0.0,	//camera up vector
								  viewMatrix);

	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, modelMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, translateMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrix);

	//call each object in the list draw function
	for (unsigned int i = 0; i < list.size(); i++)
	{
		float* tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
		
		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
		
		//calculate rotation on all 3 axis
		tempSpace = list[i]->GetRotation();
		for(int r = 0; r < 3; r++)
		{
			if (tempSpace[r] != 0.0)
			{
				switch(r)
				{
				case 0:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 1.0, 0.0, 0.0, rotationMatrix);
					break;
				case 1:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 0.0, 1.0, 0.0, rotationMatrix);
					break;
				case 2:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 0.0, 0.0, 1.0, rotationMatrix);
					break;
				}

				Matrix3D::MultMatrix(modelMatrix, rotationMatrix, modelMatrix);		
			}
		}
		
		Matrix3D::MultMatrix(modelMatrix, translateMatrix, modelMatrix);	//calculate world position
		Matrix3D::MultMatrix(modelViewMatrix, viewMatrix, modelMatrix);		//model - view matrix
		Matrix3D::MultMatrix(MVP, Engine::perspective, modelViewMatrix);	//model - view - projection matrix
		
		//update VS parameters
		simpleVS.UpdateModelViewMatrix(MVP()); 
		
		//update shaders
		simpleVS.UpdateParameters();
		simpleFS.UpdateParameters();
		
		//draw geometry
		list[i]->Draw();
	}

	//disable Vertex CGprofile
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
}

float oldTime;
void Scene::Update()
{
	float newTime = glutGet(GLUT_ELAPSED_TIME);
	std::cout << "delta time = " << newTime << " - " << oldTime << std::endl;
	//oldTime = glutGet(GLUT_ELAPSED_TIME);
	//Scene::deltaTime = (glutGet(GLUT_ELAPSED_TIME) - Scene::deltaTime) * 0.001;
	Scene::deltaTime = (newTime - oldTime) * 0.001;
	oldTime = newTime;
	float fps = 1 / (Scene::deltaTime);
	
	
	std::cout << "float delta time = " << Scene::deltaTime << " seconds " << std::endl;
	std::cout << "fps = " << fps << std::endl;

	//rotating 4th object
	list[3]->RotationAroundAxis(50 * Scene::deltaTime, 0.0, 0.0);

	//call each object in the list update function
	//for (unsigned int i = 0; i < list.size(); i++)
	//{
	//	list[i]->Update();
	//}
}

// return compiler error message when setting up shader programs
void Scene::checkForCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		printf("%s: %s: %s\n",
			"OpenGLVer2", situation, string);
		if (error == CG_COMPILER_ERROR) 
		{
			printf("%s\n", cgGetLastListing(rendererGL.GetContext()));
		}
		
		char x;
		std::cin >> x;

		exit(1);
	}
}