
#include "StdAfx.h"
#include "Scene.h"
#include "ObjectTriangle.h"
#include "Matrix3D.h"
#include "Engine.h"
#include <iostream>

const char *myVertexProgramFileName = "vertex_shader.cg",
			*myVertexProgramName = "Test",
			*myFragmentProgramFileName = "fragment_shader.cg",
			*myFragmentProgramName = "pixelShader";

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

void Scene::Init()
{
	myCgContext = cgCreateContext();
	checkForCgError("creating context");
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);
	
	myCgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(myCgVertexProfile);
	checkForCgError("selecting vertex profile");

	myCgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(myCgFragmentProfile);
	checkForCgError("selecting fragment profile");

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

	//Loads the vertex program into memory
	//cgGLLoadProgram(myCgFragmentProgram);
	checkForCgError("Loading program");


	//This is where we add objects

	//camera object should be added in the constructor
	list.push_back(new ObjectTriangle());
	//list.push_back(new ObjectTriangle(-0.5, -0.5, 1.0));
	//list.push_back(new ObjectTriangle(0.5, 0.0, 0.5));
}

void Scene::Draw()
{
	glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Start using CG program (First we bind)
	cgGLBindProgram(myCgVertexProgram);
	checkForCgError("Binding vertex program");

	//Enable profiles
	cgGLEnableProfile(myCgVertexProfile);
	checkForCgError("Enabling vertex profile");
	
	Matrix3D viewMatrix;
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, 5, 
								  0.0, 0.0, 0.0,
								  0.0, 1.0, 0.0,
								  viewMatrix);

	Matrix3D MVP, modelViewMatrix, modelMatrix;

	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, modelMatrix);

	/*Matrix3D translateMatrix, rotateMatrix;*/

	//	Matrix3D::MakeRotateMatrix(0, 0, 1, 0, rotateMatrix);
	//Matrix3D::MakeTranslateMatrix(0, 0, 0, translateMatrix);
	//Matrix3D::MultMatrix(modelMatrix, translateMatrix, rotateMatrix);

	//This is where we draw stuff
	for (unsigned int i=0; i<list.size(); i++)
	{
		/* modelViewMatrix = viewMatrix * modelMatrix */
		Matrix3D::MultMatrix(modelViewMatrix, viewMatrix, modelMatrix);

		/* modelViewProj = projectionMatrix * modelViewMatrix */
		Matrix3D::MultMatrix(MVP, Engine::perspective, modelViewMatrix);
		
		cgSetMatrixParameterfr(myCgVertexParam_modelViewProj, MVP());	//pass MVP as pointer
		cgUpdateProgramParameters(myCgVertexProgram);
		list[i]->Draw();
	}

	/*cout << "From draw function - MVP" << endl;
	Engine::PrintMatrix(MVP);*/
}

void Scene::Update()
{
	//This is where we update stuff
	for (unsigned int i=0; i<list.size(); i++)
	{
		list[i]->Update();
	}
}

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