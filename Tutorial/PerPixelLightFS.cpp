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