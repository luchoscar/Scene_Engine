#include "stdafx.h"
#include "MultPerPixelLightFS.h"
#include "OpenGLRenderer.h"

MultPerPixelLightFS::MultPerPixelLightFS()
{
	BindSceneLisghtsNumber(0);
}

MultPerPixelLightFS::MultPerPixelLightFS(int In_lightsNum) 
{
	BindSceneLisghtsNumber(In_lightsNum);
}

MultPerPixelLightFS::~MultPerPixelLightFS()
{
}

void MultPerPixelLightFS::BindSceneLisghtsNumber(int In_maxLights)
{
	maxLights = cgGetNamedParameter(fragmentProgram, "maxLights");
	OpenGLRenderer::checkForCgError("could not get maxLights parameter");

	cgGLSetParameter1f(maxLights, In_maxLights);
	OpenGLRenderer::checkForCgError("setting light position");
}

void MultPerPixelLightFS::LinkParameters()
{
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");

	normalMap = cgGetNamedParameter(fragmentProgram, "normalMap");
	OpenGLRenderer::checkForCgError("could not get normalMap parameter");

	lightColor[0] = cgGetNamedParameter(fragmentProgram, "lights[0].color");
	OpenGLRenderer::checkForCgError("could not get light color [0] parameter");

	lightColor[1] = cgGetNamedParameter(fragmentProgram, "lights[1].color");
	OpenGLRenderer::checkForCgError("could not get light color [1] parameter"); 
	
	lightPossition[0] = cgGetNamedParameter(fragmentProgram, "lights[0].position");
	OpenGLRenderer::checkForCgError("could not get light position [0] parameter");

	lightPossition[1] = cgGetNamedParameter(fragmentProgram, "lights[1].position");
	OpenGLRenderer::checkForCgError("could not get light position [1] parameter"); 

	isEmissive = cgGetNamedParameter(fragmentProgram, "isEmissive");
	OpenGLRenderer::checkForCgError("could not get isEmmisive parameter");

	lightFallOffExp = cgGetNamedParameter(fragmentProgram, "lightFallOffExp");
	OpenGLRenderer::checkForCgError("could not get light falloff exponent");
}


void MultPerPixelLightFS::SetDecalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void MultPerPixelLightFS::SetNormalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(normalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void MultPerPixelLightFS::UpdateLightColor(float* lightCol, int lightId)
{
	cgGLSetParameter3fv(lightColor[lightId], lightCol);
	OpenGLRenderer::checkForCgError("setting light color");
}

void MultPerPixelLightFS::UpdateLightPosition(float* lightPos, int lightId)
{
	cgGLSetParameter3fv(lightPossition[lightId], lightPos);
	OpenGLRenderer::checkForCgError("setting light position");
}

void MultPerPixelLightFS::UpdateIsEmissive(int emisive)
{
	cgGLSetParameter1f(isEmissive, emisive);
	OpenGLRenderer::checkForCgError("setting light position");
}

void MultPerPixelLightFS::UpdateLightFallOffExp(float fallOffExp)
{
	cgGLSetParameter1f(lightFallOffExp, fallOffExp);
	OpenGLRenderer::checkForCgError("setting light fall off exponent");
}