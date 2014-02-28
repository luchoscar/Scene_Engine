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

	lightPossition[1] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[1].position");

	lightPossition[2] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[2].position");

	lightPossition[3] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[3].position");

	lightPossition[4] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[4].position");

	lightPossition[5] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[5].position");

	lightPossition[6] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[6].position");

	lightColor[0] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[0].color");

	lightColor[1] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[1].color");

	lightColor[2] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[2].color");

	lightColor[3] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[3].color");

	lightColor[4] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[4].color");

	lightColor[5] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[5].color");

	lightColor[6] = OpenGLRenderer::BindCgParameter(fragmentProgram, "lights[6].color");

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