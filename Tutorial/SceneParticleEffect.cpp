#include "stdafx.h"
#include "SceneParticleEffect.h"
#include "ObjectPlane.h"
#include "ObjectCube.h"
#include "Engine.h"

SceneParticleEffect::SceneParticleEffect()
{
}


SceneParticleEffect::~SceneParticleEffect()
{
}

void SceneParticleEffect::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	// creating GS profile
	rendererGL.InitGeometryProfile();

	/*** light object shader ***/
	//creating VS program
	simpleVS.CreateProgram("vertex_shader.cg", "VS_program");
	rendererGL.LoadProgram(simpleVS.GetProgram());
	simpleVS.LinkParameters();

	//creating FS program
	simpleFS.CreateProgram("fragment_shader.cg", "FS_program");
	rendererGL.LoadProgram(simpleFS.GetProgram());
	simpleFS.LinkParameters();

	/*** room objects shader ***/
	//creating VS program
	pixelLightVS.CreateProgram("vertex_multPixelLights.cg", "VS_multPixelLight");
	rendererGL.LoadProgram(pixelLightVS.GetProgram());
	pixelLightVS.LinkParameters();

	//creating FS program
	pixelLightFS.CreateProgram("fragment_multPixelLights.cg", "FS_multPixelLight");
	rendererGL.LoadProgram(pixelLightFS.GetProgram());
	pixelLightFS.LinkParameters();

	/*** particle shader ***/
	//creating GS program
	billboardsGS.CreateProgram("geometry_billboard.cg", "GS_billboard");
	rendererGL.LoadProgram(billboardsGS.GetProgram());
	billboardsGS.LinkParameters();
	billboardsGS.UpdateBillboardSize(10.0f);

	//loading textures
	textureManager.Init(2);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	textureManager.setBmpTextureinMap("../Images/bricks_normal.bmp");
	
	//light objects
	//initializing light variables
	maxLights = 1;

	lightFallOffExp = 1.0;
	pixelLightFS.UpdateLightFallOffExp(lightFallOffExp);

	specularPower = 100.0f;
	pixelLightFS.UpdateSpeculatPower(specularPower);

	for (int i = 0; i < maxLights; i++)
	{
		//list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.025f, 0.025f, 0.025f, 1.0f, 1.0f, 1.01f));
		list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.01f));
	}

	//camera object
	cameraObject = new ObjectCamera(0.0f, 0.0f, -2.5f,
		0.0f, 1.0f, 0.0,
		0.0f, 0.0f, 0.0);

	cameraObject->Init();

	//loading room
	//back wall
	list.push_back(new ObjectPlane(1.0f, 1.0f, 2.0f,
		90.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, 1.0f, 2.0f,
		90.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(1.0f, -1.0f, 2.0f,
		90.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, -1.0f, 2.0f,
		90.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	//right wall
	list.push_back(new ObjectPlane(-2.0f, 1.0f, 1.0f,
		90.0f, 0.0f, 90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-2.0f, 1.0f, -1.0f,
		90.0f, 0.0f, 90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-2.0f, -1.0f, 1.0f,
		270.0f, 0.0f, 90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-2.0f, -1.0f, -1.0f,
		270.0f, 0.0f, 90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	//floor
	list.push_back(new ObjectPlane(1.0f, -2.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, -2.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(1.0f, -2.0f, -1.0f,
		0.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, -2.0f, -1.0f,
		0.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	//left wall
	list.push_back(new ObjectPlane(2.0f, 1.0f, 1.0f,
		90.0f, 0.0f, -90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(2.0f, 1.0f, -1.0f,
		90.0f, 0.0f, -90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(2.0f, -1.0f, 1.0f,
		270.0f, 0.0f, -90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(2.0f, -1.0f, -1.0f,
		270.0f, 0.0f, -90.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	//roof
	list.push_back(new ObjectPlane(1.0f, 2.00f, 1.0f,
		180.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, 2.00f, 1.0f,
		180.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(1.0f, 2.00f, -1.0f,
		180.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, 2.00f, -1.0f,
		180.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	//front wall
	list.push_back(new ObjectPlane(1.0f, 1.0f, -2.0f,
		-90.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, 1.0f, -2.0f,
		-90.0f, 180.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(1.0f, -1.0f, -2.0f,
		-90.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
	list.push_back(new ObjectPlane(-1.0f, -1.0f, -2.0f,
		-90.0f, 0.0f, 0.0f,
		2.0f, 2.0, 2.0f,
		1.0f, 1.0f, 1.0f));
}

void SceneParticleEffect::Draw()
{
	rendererGL.ClearGLFlags();

	Matrix3D MVP, viewMatrix, modelMatrix, translateMatrix,
		rotationMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ,
		modelToWorld, viewProjection;

	cameraObject->CalculateViewMatrix();
	viewMatrix = cameraObject->GetViewMatrix();

	Matrix3D::MultMatrix(viewProjection, Engine::perspective, viewMatrix);	//model - view - projection matrix
	float* tempSpace;

	/*** light object ***/
	//bind CG program
	rendererGL.BindProgram(simpleVS.GetProgram());
	rendererGL.BindProgram(simpleFS.GetProgram());
	rendererGL.BindProgram(billboardsGS.GetProgram());

	//Enable VS & FS profiles
	rendererGL.EnableProfile(rendererGL.GetVertexProfile());
	rendererGL.EnableProfile(rendererGL.GetFragmentProfile());
	rendererGL.EnableProfile(rendererGL.GetGeometryProfile());

	billboardsGS.UpdateCameraPosition(cameraObject->GetPosition());
	billboardsGS.UpdateMatrixMVP(MVP());
	
	//for (int i = 0; i < maxLights; i++)
	for (int i = 0; i < 1; i++)
	{
		float* position = new float[3];
		position[0] = 0 + 2 * i;
		position[1] = 0;
		position[2] = 0;

		tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
		Matrix3D::MultMatrix(modelToWorld, translateMatrix, modelMatrix);
		Matrix3D::MultMatrix(MVP, viewProjection, modelToWorld);

		simpleVS.UpdateModelViewMatrix(MVP());

		simpleVS.UpdateParameters();
		simpleFS.UpdateParameters();
		billboardsGS.UpdateParameters();

		list[i]->Draw();
	}

	//disable CGprofiles
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
	rendererGL.DisableProfile(rendererGL.GetGeometryProfile());

	/*** room objects ***/
	//bind CG program
	rendererGL.BindProgram(pixelLightVS.GetProgram());
	rendererGL.BindProgram(pixelLightFS.GetProgram());

	//Enable VS & FS profiles
	rendererGL.EnableProfile(rendererGL.GetVertexProfile());
	rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

	//call each object in the list draw function
	for (unsigned int i = maxLights; i < list.size(); i++)
	{
		//update matrices parameters
		tempSpace = list[i]->GetScale();
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
		Matrix3D::MultMatrix(modelToWorld, translateMatrix, modelMatrix);
		Matrix3D::MultMatrix(MVP, viewProjection, modelToWorld);

		//update tangent and bitangent parameters
		float tangent[3] = { 1.0f, 0.0f, 0.0f };
		float bitangent[3] = { 0.0f, 0.0f, 1.0f };

		pixelLightVS.UpdateTangent(tangent);
		pixelLightVS.UpdateBitangent(bitangent);

		pixelLightVS.UpdateMatrixMVP(MVP());

		pixelLightFS.UpdateMatrixModelWorld(modelToWorld());

		//update light parameters
		for (int c = 0; c < maxLights; c++)
		{
			pixelLightFS.UpdateLightPosition(list[c]->GetPosition(), c);
			pixelLightFS.UpdateLightColor(list[c]->GetColor(), c);
		}

		pixelLightFS.UpdateCameraPosition(cameraObject->GetPosition());

		//update textures parameters
		pixelLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_diffuse.bmp"));
		pixelLightFS.SetNormalMap(textureManager.getTextureId("../Images/bricks_normal.bmp"));

		//update shaders
		pixelLightVS.UpdateParameters();
		pixelLightFS.UpdateParameters();
		
		list[i]->Draw();
	}

	//disable Vertex CGprofile
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
}

void SceneParticleEffect::Update()
{

}
