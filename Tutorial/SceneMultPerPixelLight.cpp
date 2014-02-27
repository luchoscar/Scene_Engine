#include "stdafx.h"
#include "SceneMultPerPixelLight.h"
#include "ObjectPlane.h"
#include "ObjectCube.h"

SceneMultPerPixelLight::SceneMultPerPixelLight()
{
}


SceneMultPerPixelLight::~SceneMultPerPixelLight()
{
}


void SceneMultPerPixelLight::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

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
	
	//initializing light variables
	maxLights = 7;
	
	lightAngle = new float[maxLights];
	for (int i = 0; i < maxLights; i++)
		lightAngle[i] = 0.0f;

	lightRadMov = new float[maxLights];
	for (int i = 0; i < maxLights; i++)
		lightRadMov[i] = 1.8f;

	lightFallOffExp = 1.75f;
	pixelLightFS.UpdateLightFallOffExp(lightFallOffExp);

	specularPower = 100.0f;
	pixelLightFS.UpdateSpeculatPower(specularPower);

	lightAngleDelta = new float[maxLights];
	for (int i = 0; i < maxLights; i++)
	{
		lightAngleDelta[i] = (30.0f * static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + 5.0) * Matrix3D::myPi / 180.0f;

		if (i % 2) lightAngleDelta[i] *= -1;

		float color[3];

		for (int c = 0; c < 3; c++)
			color[c] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.025f, 0.025f, 0.025f, color[0], color[1], color[2]));
	}

	//initializing camera variables
	cameraPosAngle = 0.0f;
	cameraPosRadMov = 1.5f;
	cameraPosAngleDelta = 8.75 * Matrix3D::myPi / 180.0f;

	cameraObject = new ObjectCamera(0.0f, 0.0f, -2.5f,
									0.0f, 1.0f, 0.0,
									0.0f, 0.0f, 0.0);

	cameraObject->Init();

	//loading textures
	textureManager.Init(2);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	textureManager.setBmpTextureinMap("../Images/bricks_normal.bmp");

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

void SceneMultPerPixelLight::Draw()
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

	//Enable VS & FS profiles
	rendererGL.EnableProfile(rendererGL.GetVertexProfile());
	rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

	for (int i = 0; i < maxLights; i++)
	{
		tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
		Matrix3D::MultMatrix(modelToWorld, translateMatrix, modelMatrix);
		Matrix3D::MultMatrix(MVP, viewProjection, modelToWorld);

		simpleVS.UpdateModelViewMatrix(MVP());

		simpleVS.UpdateParameters();
		simpleFS.UpdateParameters();

		list[i]->Draw();
	}

	//disable CGprofiles
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());

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

		OpenGLRenderer::EnableTexture(pixelLightFS.GetDecalMap());
		OpenGLRenderer::EnableTexture(pixelLightFS.GetNormalMap());

		//update shaders
		pixelLightVS.UpdateParameters();
		pixelLightFS.UpdateParameters();

		list[i]->Draw();
	}

	//disable Vertex CGprofile
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
}

void SceneMultPerPixelLight::Update()
{
	//rotate light around origin on xyz coordinates
	for (int i = 0; i < maxLights; i++)
	{
		lightAngle[i] += lightAngleDelta[i] * Engine::deltaTime;

		if (lightAngle[i] > (Matrix3D::myPi + Matrix3D::myPi))
			lightAngle[i] -= (Matrix3D::myPi + Matrix3D::myPi);
		else if (lightAngle[i] < -(Matrix3D::myPi + Matrix3D::myPi))
			lightAngle[i] += (Matrix3D::myPi + Matrix3D::myPi);

		float lightRadDelta = lightRadMov[i];

		if (i % 2 == 0)
			list[i]->SetPosition(cos(lightAngle[i]) * lightRadDelta, cos(lightAngle[i]) * lightRadDelta, sin(lightAngle[i]) * lightRadDelta);
		else
			list[i]->SetPosition(cos(lightAngle[i]) * lightRadDelta, sin(lightAngle[i]) * lightRadDelta, sin(lightAngle[i]) * lightRadDelta);
	}

	////rotate camera on xz coordinates and look up and down
	//cameraPosAngle += cameraPosAngleDelta * Engine::deltaTime;

	//if (cameraPosAngle > (Matrix3D::myPi + Matrix3D::myPi))
	//	cameraPosAngle -= (Matrix3D::myPi + Matrix3D::myPi);

	//float* cameraUpdate = new float[3];
	////update for position
	//cameraUpdate[0] = cos(cameraPosAngle) * cameraPosRadMov;
	//cameraUpdate[1] = sin(cameraPosAngle) * cameraPosRadMov;

	////update for look at
	//cameraUpdate[2] = cos(cameraPosAngle);

	//cameraObject->SetPosition(cameraUpdate[0], cameraObject->GetPosition()[1], cameraUpdate[1]);
	//cameraObject->SetLookAtVector(cameraObject->GetLookAtVector()[0], cameraUpdate[2], cameraObject->GetLookAtVector()[2]);
}
