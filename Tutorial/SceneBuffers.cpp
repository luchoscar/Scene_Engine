#include "stdafx.h"
#include "SceneBuffers.h"
#include "ObjectCube.h"
#include "Engine.h"

SceneBuffers::SceneBuffers()
{
	lightPos[0] = 10.0f;
	lightPos[1] = 10.0f;
	lightPos[2] = 0.0f;

	lightRad = 1.0;
	angleLightRot = 0.0;
	anfleDelta = 20.0f;
}


SceneBuffers::~SceneBuffers()
{
}


void SceneBuffers::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	//creating VS program
	vertexLightVS.CreateProgram("vertex_vertexLight.cg", "VS_vertexLight");
	rendererGL.LoadProgram(vertexLightVS.GetProgram());
	vertexLightVS.LinkParameters();

	//creating FS program
	vertexLightFS.CreateProgram("fragment_vertexLight.cg", "FS_vertexLight");
	rendererGL.LoadProgram(vertexLightFS.GetProgram());
	vertexLightFS.LinkParameters();

	//set light color
	float color[3] = { 1.0, 1.0, 1.0 };
	vertexLightFS.UpdateLightColor(color);

	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 30.0f, 45.0f, 15.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.25f, 0.25f, 0.5f, 0.5f, 0.5f));
	
	//loading bmp
	textureManager.Init(2);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	textureManager.setBmpTextureinMap("../Images/bricks_normal.bmp");
}

void SceneBuffers::Draw()
{
	rendererGL.ClearGLFlags();

	Matrix3D MVP, viewMatrix, modelViewMatrix, modelMatrix, rotationMatrix,
		translateMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ,
		modelToWorld, viewProjection;

	Matrix3D::BuildLookAtMatrix(0.0, 1.0, -5.0,	//camera position
								0.0, 0.0, 0.0,	//point that camera looks at
								0.0, 1.0, 0.0,	//camera up vector
								viewMatrix);

	//create identity matrices
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, modelMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, translateMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrixX);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrixY);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrixZ);

	//call each object in the list draw function
	for (unsigned int i = 0; i < list.size(); i++)
	{
		float* tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);

		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);

		//calculate rotation on all 3 axis
		tempSpace = list[i]->GetRotation();
		Matrix3D::MakeRotateMatrix(tempSpace[0], 1.0, 0.0, 0.0, rotationMatrixX);
		Matrix3D::MakeRotateMatrix(tempSpace[1], 0.0, 1.0, 0.0, rotationMatrixY);
		Matrix3D::MakeRotateMatrix(tempSpace[2], 0.0, 0.0, 1.0, rotationMatrixZ);
		Matrix3D::MultMatrix(rotationMatrix, rotationMatrixX, rotationMatrixY);
		Matrix3D::MultMatrix(rotationMatrix, rotationMatrix, rotationMatrixZ);

		Matrix3D::MultMatrix(modelMatrix, rotationMatrix, modelMatrix);

		Matrix3D::MultMatrix(modelMatrix, translateMatrix, modelMatrix);	//calculate world position
		Matrix3D::MultMatrix(modelToWorld, translateMatrix, modelMatrix);	//calculate world position

		Matrix3D::MultMatrix(modelViewMatrix, viewMatrix, modelMatrix);		//model - view matrix
		Matrix3D::MultMatrix(MVP, Engine::perspective, modelViewMatrix);	//model - view - projection matrix
		Matrix3D::MultMatrix(viewProjection, Engine::perspective, viewMatrix);	//model - view - projection matrix

		//bind CG program
		rendererGL.BindProgram(vertexLightVS.GetProgram());
		rendererGL.BindProgram(vertexLightFS.GetProgram());

		//Enable VS & FS profiles
		rendererGL.EnableProfile(rendererGL.GetVertexProfile());
		rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

		//update shaders parameters

		vertexLightVS.UpdateModelViewMatrix(MVP());
		vertexLightVS.UpdateMatrixModelWorld(modelToWorld());
		vertexLightVS.UpdateMatrixViewProj(viewProjection());
		vertexLightVS.UpdateLightPosition(lightPos);

		if (i != 1)
			vertexLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_diffuse.bmp"));
		else
			vertexLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_normal.bmp"));

		//update shaders
		vertexLightVS.UpdateParameters();
		vertexLightFS.UpdateParameters();

		list[i]->DrawBuffers();

		//disable Vertex CGprofile
		rendererGL.DisableProfile(rendererGL.GetVertexProfile());
		rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
	}
}

void SceneBuffers::Update()
{
	angleLightRot += Engine::deltaTime * (anfleDelta * 3.1416 / 180);

	if (angleLightRot >= 3.1416 * 2.0)
		angleLightRot = 0.0f;

	lightPos[0] = sin(angleLightRot) * lightRad;
	lightPos[1] = sin(angleLightRot * 2.0) * lightRad;
	lightPos[2] = cos(angleLightRot) * lightRad;

	list[1]->SetPosition(lightPos[0], lightPos[1], lightPos[2]);
}