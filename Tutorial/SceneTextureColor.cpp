/****************************************************************************
 * Scene to control game logic - eventually to be made into a hierarchy		*
 * in order to implement a Vector<SceneBase> from Engine.cpp				*
 * Logic to create, enable and disable VS & FS to be moved to its own		*
 * hierarchy system															*
 * Camera to be set as its own derived class from BaseObject				*
 ****************************************************************************/

#include "StdAfx.h"
#include "SceneTextureColor.h"
#include "ObjectTriangle.h"
#include "ObjectCube.h"

//SOIL Image library - SOIL commands to be moved to OpenGLRenderer class
#include "..\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "..\\Simple OpenGL Image Library\\projects\\VC9\\Debug\\SOIL.lib")

SceneTextureColor::SceneTextureColor(void)
{

}

SceneTextureColor::~SceneTextureColor(void)
{
	
}

//initializing scene
void SceneTextureColor::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	//creating VS program
	simpleVS.CreateProgram("vertex_shader.cg", "VS_program");
	rendererGL.LoadProgram(simpleVS.GetProgram());
	simpleVS.LinkParameters();

	//creating FS program
	simpleFS.CreateProgram("fragment_shader.cg", "FS_program");
	rendererGL.LoadProgram(simpleFS.GetProgram());
	simpleFS.LinkParameters();
	
	//create FS program
	textureFS.CreateProgram("textureFragment.cg", "FS_program");
	rendererGL.LoadProgram(textureFS.GetProgram());
	textureFS.LinkParameters();
	
	//loading bmp
	textureManager.Init(1);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	
	//adding default scene objects
	//camera object should be added in the constructor and as the first object of the list for easy access
	list.push_back(new ObjectTriangle());
	list.push_back(new ObjectTriangle(-1.5, 1.75, 0.0, 0.0, 0.0, 0.0, 3.0, 3.0, 3.0, 0.75, 0.25, 0.5));
	list.push_back(new ObjectCube(-1.5, 1.5, -2.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 1.0, 0.5, 0.0));
	list.push_back(new ObjectCube(1.5, -0.70, 0.0, 25.0, 30.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
}

void SceneTextureColor::Draw()
{
	rendererGL.ClearGLFlags();

	Matrix3D MVP, viewMatrix, modelViewMatrix, modelMatrix, translateMatrix, rotationMatrix;
	
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, -12.5,	//camera position
								  0.0, 0.0, 0.0,	//point that camera looks at
								  0.0, 1.0, 0.0,	//camera up vector
								  viewMatrix);

	//create identity matrices
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
		
		int oddVal = i % 2;
		//bind CG program
		rendererGL.BindProgram(simpleVS.GetProgram());
		
		if (oddVal != 0)
			rendererGL.BindProgram(simpleFS.GetProgram());
		else
			rendererGL.BindProgram(textureFS.GetProgram());

		//Enable VS & FS profiles
		rendererGL.EnableProfile(rendererGL.GetVertexProfile());
		rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

		//update simpleVS parameters
		simpleVS.UpdateModelViewMatrix(MVP()); 
		
		if (!oddVal)
		{
			textureFS.SetTextureParameter(textureManager.getTextureId("../Images/bricks_diffuse.bmp"));
		}

		//update shaders
		simpleVS.UpdateParameters();
		
		if (oddVal)
			simpleFS.UpdateParameters();
		else
			textureFS.UpdateParameters();

		//draw geometry
		list[i]->Draw();

		//disable Vertex CGprofile
		rendererGL.DisableProfile(rendererGL.GetVertexProfile());
		rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
	}
}

float boundBox = 5;
int xDir = 1;
int yDir = 1;
int zDir = 1;
void SceneTextureColor::Update()
{
	//translate 3rd object on x-axis
	if (list[2]->GetPosition()[0] <= -boundBox) 
	{
		list[2]->SetPosition(-boundBox, list[2]->GetPosition()[1], list[2]->GetPosition()[2]);
		xDir = 1;
	}
	else if (list[2]->GetPosition()[0] >= boundBox) 
	{
		list[2]->SetPosition(boundBox, list[2]->GetPosition()[1], list[2]->GetPosition()[2]);
		xDir = -1;
	}

	//translate 3rd object on y-axis
	if (list[2]->GetPosition()[1] <= -boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], -boundBox, list[2]->GetPosition()[2]);
		yDir = 1;
	}
	else if (list[2]->GetPosition()[1] >= boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], boundBox, list[2]->GetPosition()[2]);
		yDir = -1;
	}

	//translate 3rd object on z-axis
	if (list[2]->GetPosition()[2] <= -boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], list[2]->GetPosition()[1], -boundBox);
		zDir = 1;
	}
	else if (list[2]->GetPosition()[2] >= boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], list[2]->GetPosition()[1], boundBox);
		zDir = -1;
	}
	list[2]->TranslateOnAxis(xDir * 5.0 * Engine::deltaTime, yDir * 2.5 * Engine::deltaTime, zDir * 7.5 * Engine::deltaTime);

	//rotating 3rd & 4th object
	list[1]->RotationAroundAxis(0.0, 25 * Engine::deltaTime, 0.0); 
	list[2]->RotationAroundAxis(15 * Engine::deltaTime, 20 * Engine::deltaTime, 30 * Engine::deltaTime);
	list[3]->RotationAroundAxis(0.0, 50 * Engine::deltaTime, 0.0);
}