#include "stdafx.h"
#include "VertexLightFS.h"
#include "OpenGLRenderer.h"

VertexLightFS::VertexLightFS()
{
}


VertexLightFS::~VertexLightFS()
{
}

void VertexLightFS::LinkParameters()
{
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");

	normalMap = cgGetNamedParameter(fragmentProgram, "normalMap");
	OpenGLRenderer::checkForCgError("could not get normalMap parameter");

	lightColor = cgGetNamedParameter(fragmentProgram, "lightColor");
	OpenGLRenderer::checkForCgError("could not get lightColor parameter");
}


void VertexLightFS::SetDecalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void VertexLightFS::SetNormalMap(GLuint textureParam)
{
	glBindTexture(GL_TEXTURE_2D, textureParam);
	cgGLSetTextureParameter(normalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}

void VertexLightFS::UpdateLightColor(float* lightCol)
{
	cgGLSetParameter3fv(lightColor, lightCol);
	OpenGLRenderer::checkForCgError("setting light color");
}
