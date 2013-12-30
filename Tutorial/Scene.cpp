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

float Scene::deltaTime;

Scene::Scene(void)
{
	//camera object should be added in the constructor and as the first object of the list for easy access
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
	//creating CG context
	myCgContext = cgCreateContext();
	checkForCgError("creating context");
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);
	
	//creating VS profile
	myCgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(myCgVertexProfile);
	checkForCgError("selecting vertex profile");

	//creating FS profile
	myCgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(myCgFragmentProfile);
	checkForCgError("selecting fragment profile");

	//creating VS program
	myCgVertexProgram = cgCreateProgramFromFile(
		myCgContext, 
		CG_SOURCE, 
		myVertexProgramFileName, //File name of shader program
		myCgVertexProfile,
		myVertexProgramName, //Entry function
		NULL);
	checkForCgError("Creating program from file");

	//Loads the vertex program into memory
	cgGLLoadProgram(myCgVertexProgram);
	checkForCgError("Loading program");

	//creating FS program
	myCgVertexParam_modelViewProj = cgGetNamedParameter(myCgVertexProgram, "modelViewProj");
	checkForCgError("could not get modelViewProj parameter");

	myCgFragmentProgram = cgCreateProgramFromFile(
		myCgContext, 
		CG_SOURCE, 
		myFragmentProgramFileName, //File name of shader program
		myCgFragmentProfile,
		myFragmentProgramName, //Entry function
		NULL);
	checkForCgError("Creating program from file");

	//Loads the fragment program into memory
	cgGLLoadProgram(myCgFragmentProgram);
	checkForCgError("Loading program");


	//adding default scene objects
	//camera object should be added in the constructor and as the first object of the list for easy access
	list.push_back(new ObjectTriangle());
	list.push_back(new ObjectTriangle(0.5, 1.75, 0.0, 0.0, 0.0, 30.0, 1.5, 1.5, 1.5, 1.0, 0.5, 0.25));
	list.push_back(new ObjectCube(-1.5, 1.5, -2.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
	list.push_back(new ObjectCube(1.5, -0.70, 0.0, 25.0, 30.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
}

void Scene::Draw()
{
	glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // --> adding this in order to perform depth test??? this was not being applied when called in Engine.cpp

	//bind CG program
	cgGLBindProgram(myCgVertexProgram);
	checkForCgError("Binding vertex program");

	//Enable VS & FS profiles
	cgGLEnableProfile(myCgVertexProfile);
	checkForCgError("Enabling vertex profile");
	cgGLEnableProfile(myCgFragmentProfile);
	checkForCgError("Enabling fragment profile");

	Matrix3D MVP, viewMatrix, modelViewMatrix, modelMatrix, translateMatrix, rotationMatrix;
	
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, 5, 
								  0.0, 0.0, 0.0,
								  0.0, 1.0, 0.0,
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
		
		cgSetMatrixParameterfr(myCgVertexParam_modelViewProj, MVP());	//pass MVP as pointer to VS 
		
		//update shaders
		cgUpdateProgramParameters(myCgVertexProgram);
		cgUpdateProgramParameters(myCgFragmentProgram);
		
		//draw geometry
		list[i]->Draw();

		//enable vertex and color buffers
		//glBindBuffer(GL_ARRAY_BUFFER, *list[i]->GetColorBuffer());
		//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), list[i]->GetColorBuffer(), GL_STREAM_DRAW);
		//glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);

		//glBindBuffer(GL_ARRAY_BUFFER, *list[i]->GetPosition());
		//glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), list[i]->GetPosition(), GL_STREAM_DRAW);
		//glVertexPointer(3, GL_FLOAT, 0, 0);

		//glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);

		//glDrawArrays(GL_TRIANGLES, 0, *list[i]->GetPosition());

		//glDisableClientState(GL_COLOR_ARRAY);
		//glDisableClientState(GL_VERTEX_ARRAY); 
	}

	//disable CGprofile
	cgGLDisableProfile(myCgVertexProfile);
}

void Scene::Update()
{
	Scene::deltaTime = glutGet(GLUT_ELAPSED_TIME) * 0.001 - Scene::deltaTime;
	int fps = 1 / Scene::deltaTime;
	
	std::cout << "float delta time = " << Scene::deltaTime << std::endl;
	std::cout << "fps = " << fps << std::endl;

	int deltaTime = 0;

	//call each object in the list update function
	for (unsigned int i = 0; i < list.size(); i++)
	{
		list[i]->Update(deltaTime);
	}
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
			printf("%s\n", cgGetLastListing(myCgContext));
		}
		
		char x;
		std::cin >> x;

		exit(1);
	}
}