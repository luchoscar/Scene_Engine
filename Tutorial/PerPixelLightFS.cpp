#include "stdafx.h"
#include "PerPixelLightFS.h"
#include "OpenGLRenderer.h"

PerPixelLightFS::PerPixelLightFS()
{
}


PerPixelLightFS::~PerPixelLightFS()
{
}

void PerPixelLightFS::LinkParameters()
{
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");

	normalMap = cgGetNamedParameter(fragmentProgram, "normalMap");
	OpenGLRenderer::checkForCgError("could not get normalMap parameter");

	lightColor = cgGetNamedParameter(fragmentProgram, "lightColor");
	OpenGLRenderer::checkForCgError("could not get lightColor parameter");

	lightFallOffExp = cgGetNamedParameter(fragmentProgram, "lightFallOffExp");
	OpenGLRenderer::checkForCgError("could not get light falloff exponent");
}


void PerPixelLightFS::SetDecalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void PerPixelLightFS::SetNormalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(normalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void PerPixelLightFS::UpdateLightColor(float* lightCol)
{
	cgGLSetParameter3fv(lightColor, lightCol);
	OpenGLRenderer::checkForCgError("setting light color");
}

void PerPixelLightFS::UpdateLightFallOffExp(float fallOffExp)
{
	cgGLSetParameter1f(lightFallOffExp, fallOffExp);
	OpenGLRenderer::checkForCgError("setting light fall off exponent");
}