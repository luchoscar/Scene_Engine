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
#include "Matrix3D.h"
#include "Engine.h"
#include <iostream>

const char *myVertexProgramFileName = "vertex_shader.cg",
			*myVertexProgramName = "VS_program",
			*myFragmentProgramFileName = "fragment_shader.cg",
			*myFragmentProgramName = "FS_program";

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
	list.push_back(new ObjectTriangle(0.5, 0.75, 0.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.25));
}

void Scene::Draw()
{
	glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bind CG program
	cgGLBindProgram(myCgVertexProgram);
	checkForCgError("Binding vertex program");

	//Enable VS & FS profiles
	cgGLEnableProfile(myCgVertexProfile);
	checkForCgError("Enabling vertex profile");
	cgGLEnableProfile(myCgFragmentProfile);
	checkForCgError("Enabling fragment profile");

	Matrix3D viewMatrix, MVP, modelViewMatrix, modelMatrix, translateMatrix, rotationMatrix;
	
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, 5, 
								  0.0, 0.0, 0.0,
								  0.0, 1.0, 0.0,
								  viewMatrix);

	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, modelMatrix);

	//call each object in the list draw function
	for (unsigned int i=0; i < list.size(); i++)
	{
		float* tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
		
		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
		
		Matrix3D::MultMatrix(modelMatrix, translateMatrix, modelMatrix);	//calculate world position
		Matrix3D::MultMatrix(modelViewMatrix, viewMatrix, modelMatrix);
		Matrix3D::MultMatrix(MVP, Engine::perspective, modelViewMatrix);
		
		cgSetMatrixParameterfr(myCgVertexParam_modelViewProj, MVP());	//pass MVP as pointer to VS 
		cgUpdateProgramParameters(myCgVertexProgram);
		cgUpdateProgramParameters(myCgFragmentProgram);
		list[i]->Draw();
	}

	//disable CGprofile
	cgGLDisableProfile(myCgVertexProfile);
}

void Scene::Update()
{
	//call each object in the list update function
	for (unsigned int i=0; i<list.size(); i++)
	{
		list[i]->Update();
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