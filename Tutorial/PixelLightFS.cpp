#include "stdafx.h"
#include "PixelLightFS.h"
#include "OpenGLRenderer.h"

PixelLightFS::PixelLightFS()
{
}


PixelLightFS::~PixelLightFS()
{
}

void PixelLightFS::LinkParameters()
{
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");

	normalMap = cgGetNamedParameter(fragmentProgram, "normalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");
}

void PixelLightFS::SetDecalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void PixelLightFS::SetNormalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(normalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}
