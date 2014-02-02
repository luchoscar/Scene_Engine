#include "stdafx.h"
#include "ScenePerPixelLight.h"
#include "ObjectPlane.h"
#include "ObjectCube.h"

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
	pixelLightVS.CreateProgram("vertex_vertexLight.cg", "VS_vertexLight");
	rendererGL.LoadProgram(pixelLightVS.GetProgram());
	pixelLightVS.LinkParameters();

	//creating FS program
	pixelLightFS.CreateProgram("fragment_vertexLight.cg", "FS_vertexLight");
	rendererGL.LoadProgram(pixelLightFS.GetProgram());
	pixelLightFS.LinkParameters();

	//initializig light variables
	cameraPosition[0] = 0.0;
	cameraPosition[1] = 0.0;
	cameraPosition[2] = -1.5;

	lightAngle = 0.0f;
	lightAngleDelta = 10.0f * Matrix3D::myPi / 180.0f;

	list.push_back(new ObjectCube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.025f, 0.025f, 0.025f, 1.0f, 1.0f, 1.0f));

	//loading textures
	textureManager.Init(2);
	textureManager.setBmpTextureinMap("../Images/bricks_diffuse.bmp");
	textureManager.setBmpTextureinMap("../Images/bricks_normal.bmp");

	//loading room
	//back wall
	list.push_back(new ObjectPlane(0.0f, 0.0f, 0.5f,
									90.0f, 0.0f, 0.0f,
									1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f)); 
	//right wall
	list.push_back(new ObjectPlane(-0.5f, 0.0f, 0.0f,
									90.0f, 0.0f, 90.0f,
									1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f));
	//floor
	list.push_back(new ObjectPlane(0.0f, -0.5f, 0.0f,
									0.0f, 0.0f, 0.0f,
									1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f));
	//left wall
	list.push_back(new ObjectPlane(0.5f, 0.0f, 0.0f,
									90.0f, 0.0f, -90.0f,
									1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f));
	//roof
	list.push_back(new ObjectPlane(0.0f, 0.5f, 0.0f,
									180.0f, 180.0f, 0.0f,
									1.0f, 1.0f, 1.0f,
									1.0f, 1.0f, 1.0f));
	
}

void ScenePerPixelLight::Draw()
{
	rendererGL.ClearGLFlags();

	Matrix3D MVP, viewMatrix, modelMatrix, translateMatrix,
				rotationMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ,
				modelToWorld, viewProjection;

	//calculate ViewProjection matrix
	Matrix3D::BuildLookAtMatrix(cameraPosition[0], cameraPosition[1], cameraPosition[2],
								0.0, 0.0, 0.0,	//point that camera looks at
								0.0, 1.0, 0.0,	//camera up vector
								viewMatrix);
	
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

	//disable Vertex CGprofile
	rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	rendererGL.DisableProfile(rendererGL.GetFragmentProfile());

	/*** room objeects ***/
	//bind CG program
	rendererGL.BindProgram(pixelLightVS.GetProgram());
	rendererGL.BindProgram(pixelLightFS.GetProgram());

	//Enable VS & FS profiles
	rendererGL.EnableProfile(rendererGL.GetVertexProfile());
	rendererGL.EnableProfile(rendererGL.GetFragmentProfile());
	
	//call each object in the list draw function
	for (unsigned int i = 1; i < list.size(); i++)
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
		//pixelLightVS.UpdateCameraPosition(cameraPosition);
		pixelLightFS.UpdateLightColor(list[0]->GetColor());

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

void ScenePerPixelLight::Update()
{
	lightAngle += lightAngleDelta * Engine::deltaTime;

	if (lightAngle >= (Matrix3D::myPi + Matrix3D::myPi))
		lightAngle = 0.0f;

	list[0]->SetPosition(cos(lightAngle) * 0.4f, sin(lightAngle) * 0.4f, sin(lightAngle) * 0.4f);
}
