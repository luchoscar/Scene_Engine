#include "stdafx.h"
#include "MultPerPixelLightFS.h"
#include "OpenGLRenderer.h"

MultPerPixelLightFS::MultPerPixelLightFS()
{

}

MultPerPixelLightFS::~MultPerPixelLightFS()
{
}

void MultPerPixelLightFS::LinkParameters()
{
	decalMap = OpenGLRenderer::BindCgParameter(fragmentProgram, "decalMap");

	normalMap = OpenGLRenderer::BindCgParameter(fragmentProgram, "normalMap");

	cameraPosition = OpenGLRenderer::BindCgParameter(fragmentProgram, "cameraPosition");

	lightPossition[0] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[0].position");
	lightColor[0] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[0].color");

	lightPossition[1] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[1].position");
	lightColor[1] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[1].color");

	lightPossition[2] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[2].position");
	lightColor[2] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[2].color");

	lightPossition[3] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[3].position");
	lightColor[3] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[3].color");

	lightPossition[4] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[4].position");
	lightColor[4] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[4].color");

	lightPossition[5] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[5].position");
	lightColor[5] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[5].color");

	lightPossition[6] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[6].position");
	lightColor[6] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[6].color");

	lightPossition[7] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[7].position");
	lightColor[7] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[7].color");

	lightPossition[8] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[8].position");
	lightColor[8] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[8].color");

	lightPossition[9] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[9].position");
	lightColor[9] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[9].color");

	lightPossition[10] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[10].position");
	lightColor[10] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[10].color"); 
	
	lightPossition[11] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[11].position");
	lightColor[11] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[11].color"); 
	
	lightFallOffExp = OpenGLRenderer::BindCgParameter(fragmentProgram, "lightFallOffExp");

	matrixModelWorld = OpenGLRenderer::BindCgParameter(fragmentProgram, "matrixModelWorld");

	specularPower = OpenGLRenderer::BindCgParameter(fragmentProgram, "specularPower");
}
	
void MultPerPixelLightFS::SetDecalMap(GLuint textureParam)
{
	OpenGLRenderer::UpdateVectorTexture2dParameter(decalMap, textureParam, "decalMap");
}

void MultPerPixelLightFS::SetNormalMap(GLuint textureParam)
{
	OpenGLRenderer::UpdateVectorTexture2dParameter(normalMap, textureParam, "normalMap");
}

void MultPerPixelLightFS::UpdateLightPosition(float* lightPos, int lightId)
{
	OpenGLRenderer::UpdateVector3dParameter(lightPossition[lightId], lightPos, "lightPossition");
}

void MultPerPixelLightFS::UpdateLightColor(float* lightCol, int lightId)
{
	OpenGLRenderer::UpdateVector3dParameter(lightColor[lightId], lightCol, "lightColor");
}

void MultPerPixelLightFS::UpdateLightFallOffExp(float fallOffExp)
{
	OpenGLRenderer::UpdateFloatParameter(lightFallOffExp, fallOffExp, "lightFallOffExp");
}

void MultPerPixelLightFS::UpdateCameraPosition(float* camPos)
{
	OpenGLRenderer::UpdateVector3dParameter(cameraPosition, camPos, "cameraPosition");
}

void MultPerPixelLightFS::UpdateMatrixModelWorld(float* matModWorld)
{
	OpenGLRenderer::UpdateMatrixParameter(matrixModelWorld, matModWorld, "matrixModelWorld");
}

void MultPerPixelLightFS::UpdateSpeculatPower(float specPower)
{
	OpenGLRenderer::UpdateFloatParameter(specularPower, specPower, "specularPower");
}