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
	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void PixelLightFS::SetNormalMap(GLuint textureParam)
{
	cgGLSetTextureParameter(normalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}
