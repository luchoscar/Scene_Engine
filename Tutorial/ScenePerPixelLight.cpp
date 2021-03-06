#include "stdafx.h"
#include "ScenePerPixelLight.h"
#include "ObjectPlane.h"
#include "ObjectCube.h"
#include "Engine.h"

ScenePerPixelLight::ScenePerPixelLight()
{
	
}


ScenePerPixelLight::~ScenePerPixelLight()
{

}

void ScenePerPixelLight::Init()
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
	pixelLightVS.CreateProgram("vertex_pixelLight.cg", "VS_pixelLight");
	rendererGL.LoadProgram(pixelLightVS.GetProgram());
	pixelLightVS.LinkParameters();

	//creating FS program
	pixelLightFS.CreateProgram("fragment_pixelLight.cg", "FS_pixelLight");
	rendererGL.LoadProgram(pixelLightFS.GetProgram());
	pixelLightFS.LinkParameters();
	cameraPosAngle = 0.0f;
	cameraPosRadMov = 2.75f;
	cameraPosAngleDelta = 8.75 * Matrix3D::myPi / 180.0f;

	//initializing camera variables
	cameraObject = new ObjectCamera(cos(cameraPosAngle) * cameraPosRadMov, 0.0f, sin(cameraPosAngle) * cameraPosRadMov,
									0.0f, 0.5f, 0.0,
									0.0f, 0.0f, 0.0f);
	cameraObject->Init();

	//initializing light variables
	lightAngle = 0.0f;
	lightRadMov = 1.75f;
	lightFallOffExp = 0.8f;
	lightAngleDelta = 15.0f * Matrix3D::myPi / 180.0f;

	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0125f, 0.0125f, 0.0125f, 1.0f, 1.0f, 1.0f));

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

void ScenePerPixelLight::Draw()
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

	tempSpace = list[0]->GetScale();
	Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
	tempSpace = list[0]->GetPosition();
	Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
	Matrix3D::MultMatrix(modelToWorld, translateMatrix, modelMatrix);
	Matrix3D::MultMatrix(MVP, viewProjection, modelToWorld);

	simpleVS.UpdateModelViewMatrix(MVP());

	simpleVS.UpdateParameters();
	simpleFS.UpdateParameters();

	list[0]->Draw();

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
	
	for (int c = 0; c < 2; c++)
	{
		if (c == 1)
		{
			OpenGLRenderer::EnableAlphaBlending();
			OpenGLRenderer::DisableFaceCulling();
		}

		//call each object in the list draw function
		for (unsigned int i = 1; i < list.size(); i++)
		{
			//update matrices parameters
			
			float *tempColor = new float[3];
			tempColor[0] = list[i]->GetColor()[0];
			tempColor[1] = list[i]->GetColor()[1];
			tempColor[2] = list[i]->GetColor()[2];

			if (c == 1)
			{
				list[i]->SetColor(5.0f, 0.1f, 0.1f);
				tempSpace = new float[3];
				tempSpace[0] = 1.0f;
				tempSpace[1] = 1.0f;
				tempSpace[2] = 1.0f;
			}
			else
				tempSpace = list[i]->GetScale();

			Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);

			
			if (c == 1)
			{
				//
				tempSpace = new float[3];
				tempSpace[0] = 0.0f;
				tempSpace[1] = 0.0f;
				tempSpace[2] = 0.0f;
			}
			else
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

			pixelLightVS.UpdateCameraPosition(cameraObject->GetPosition());

			pixelLightVS.UpdateMatrixModelWorld(modelToWorld());
			pixelLightVS.UpdateMatrixViewProj(viewProjection());

			//update tangent and bitangent parameters
			float tangent[3] = { 1.0f, 0.0f, 0.0f };
			float bitangent[3] = { 0.0f, 0.0f, 1.0f };

			pixelLightVS.UpdateTangent(tangent);
			pixelLightVS.UpdateBitangent(bitangent);

			pixelLightVS.UpdateMatrixModelWorld(modelToWorld());
			pixelLightVS.UpdateMatrixViewProj(viewProjection());

			//update light parameters
			pixelLightVS.UpdateLightPosition(list[0]->GetPosition());
			pixelLightFS.UpdateLightColor(list[0]->GetColor());
			pixelLightFS.UpdateLightFallOffExp(lightFallOffExp);

			//update textures parameters
			pixelLightFS.SetDecalMap(textureManager.getTextureId("../Images/bricks_diffuse.bmp"));
			pixelLightFS.SetNormalMap(textureManager.getTextureId("../Images/bricks_normal.bmp"));

			OpenGLRenderer::EnableTexture(pixelLightFS.GetDecalMap());
			OpenGLRenderer::EnableTexture(pixelLightFS.GetNormalMap());

			//update shaders
			pixelLightVS.UpdateParameters();
			pixelLightFS.UpdateParameters();

			list[i]->Draw();

			list[i]->SetColor(tempColor[0], tempColor[1], tempColor[2]);
		}

		if (c == 1)
		{
			OpenGLRenderer::DisableAlphaBlending();
			OpenGLRenderer::EnableFaceCulling();
		}
	}
}

void ScenePerPixelLight::Update()
{
	//rotate light around origin on xyz coordinates
	lightAngle += lightAngleDelta * Engine::deltaTime;

	if (lightAngle > (Matrix3D::myPi + Matrix3D::myPi))
		lightAngle -= (Matrix3D::myPi + Matrix3D::myPi);

	list[0]->SetPosition(cos(lightAngle) * lightRadMov, 0.0f, sin(lightAngle) * lightRadMov);

	////rotate camera on xz coordinates and look up and down
	//cameraPosAngle += cameraPosAngleDelta * Engine::deltaTime;

	//if (cameraPosAngle > (Matrix3D::myPi + Matrix3D::myPi))
	//	cameraPosAngle -= (Matrix3D::myPi + Matrix3D::myPi);

	//float* cameraUpdate = new float[3];
	////update for position
	//cameraUpdate[0] = cos(cameraPosAngle) * cameraPosRadMov;
	//cameraUpdate[1] = sin(cameraPosAngle) * cameraPosRadMov;
	//
	////update for look at
	//cameraUpdate[2] = cos(cameraPosAngle);
	//
	//cameraObject->SetPosition(cameraUpdate[0], cameraObject->GetPosition()[1], cameraUpdate[1]);
	//cameraObject->SetLookAtVector(cameraObject->GetLookAtVector()[0], cameraUpdate[2], cameraObject->GetLookAtVector()[2]);
}
