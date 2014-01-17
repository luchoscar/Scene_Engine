#include "stdafx.h"
#include "PixelLightScene.h"
#include "ObjectCube.h"

float lightPos[3] = { 10.0f, 10.0f, 0.0f };
float lightRad = 1.0;
float angleLightRot = 0.0;
float anfleDelta = 20.0f;

PixelLightScene::PixelLightScene()
{

}


PixelLightScene::~PixelLightScene()
{

}

void PixelLightScene::Init() 
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	//creating VS program
	pixelLightVS.CreateProgram("vertex_pixelLight.cg", "VS_pixelLight");
	rendererGL.LoadProgram(pixelLightVS.GetProgram());
	pixelLightVS.LinkParameters();

	//creating FS program
	pixelLightFS.CreateProgram("fragment_pixelLight.cg", "FS_PixelLight");
	rendererGL.LoadProgram(pixelLightFS.GetProgram());
	pixelLightFS.LinkParameters();

	//list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 30.0f, 30.0f, 30.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f));
	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 30.0f, 45.0f, 15.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f));
	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.25f, 0.25f, 0.5f, 0.5f, 0.5f));

	//loading bmp
	textureManager.Init(2);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	textureManager.setBmpTextureinMap("../Images/bricks_normal.bmp");
}

void PixelLightScene::Draw()
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
		rendererGL.BindProgram(pixelLightVS.GetProgram());
		rendererGL.BindProgram(pixelLightFS.GetProgram());
		
		//Enable VS & FS profiles
		rendererGL.EnableProfile(rendererGL.GetVertexProfile());
		rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

		//update shaders parameters
		
		pixelLightVS.UpdateModelViewMatrix(MVP());
		pixelLightVS.UpdateMatrixModelWorld(modelToWorld());
		pixelLightVS.UpdateMatrixViewProj(viewProjection());
		pixelLightVS.UpdateLightPosition(lightPos);
		
		if (i == 0)
			pixelLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_diffuse.bmp"));
		else
			pixelLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_normal.bmp"));

		//update shaders
		pixelLightVS.UpdateParameters();
		pixelLightFS.UpdateParameters();
		
		list[i]->Draw();

		//disable Vertex CGprofile
		rendererGL.DisableProfile(rendererGL.GetVertexProfile());
		rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
	}
}

void PixelLightScene::Update()
{
	angleLightRot += Engine::deltaTime * (anfleDelta * 3.1416 / 180);

	if (angleLightRot >= 3.1416 * 2.0)
		angleLightRot = 0.0f;

	lightPos[0] = sin(angleLightRot) * lightRad;
	lightPos[1] = sin(angleLightRot * 2.0) * lightRad;
	lightPos[2] = cos(angleLightRot) * lightRad;

	list[1]->SetPosition(lightPos[0], lightPos[1], lightPos[2]);
}