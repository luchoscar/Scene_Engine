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
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");

	normalMap = cgGetNamedParameter(fragmentProgram, "normalMap");
	OpenGLRenderer::checkForCgError("could not get normalMap parameter");

	cameraPosition = cgGetNamedParameter(fragmentProgram, "cameraPosition");
	OpenGLRenderer::checkForCgError("could not get cameraPosition parameter"); 
	
	lightPossition[0] = cgGetNamedParameter(fragmentProgram, "lights[0].position");
	OpenGLRenderer::checkForCgError("could not get light position [0] parameter");

	lightPossition[1] = cgGetNamedParameter(fragmentProgram, "lights[1].position");
	OpenGLRenderer::checkForCgError("could not get light position [1] parameter"); 

	lightColor[0] = cgGetNamedParameter(fragmentProgram, "lights[0].color");
	OpenGLRenderer::checkForCgError("could not get light color [0] parameter");

	lightColor[1] = cgGetNamedParameter(fragmentProgram, "lights[1].color");
	OpenGLRenderer::checkForCgError("could not get light color [1] parameter");
	
	lightFallOffExp = cgGetNamedParameter(fragmentProgram, "lightFallOffExp");
	OpenGLRenderer::checkForCgError("could not get light falloff exponent");

	matrixModelWorld = cgGetNamedParameter(fragmentProgram, "matrixModelWorld");
	OpenGLRenderer::checkForCgError("could not get matrixModelWorld parameter");
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

void MultPerPixelLightFS::UpdateLightPosition(float* lightPos, int lightId)
{
	cgGLSetParameter3fv(lightPossition[lightId], lightPos);
	OpenGLRenderer::checkForCgError("setting light position");
}

void MultPerPixelLightFS::UpdateLightColor(float* lightCol, int lightId)
{
	cgGLSetParameter3fv(lightColor[lightId], lightCol);
	OpenGLRenderer::checkForCgError("setting light color");
}

void MultPerPixelLightFS::UpdateLightFallOffExp(float fallOffExp)
{
	cgGLSetParameter1f(lightFallOffExp, fallOffExp);
	OpenGLRenderer::checkForCgError("setting light fall off exponent");
}

void MultPerPixelLightFS::UpdateCameraPosition(float* camPos)
{
	cgGLSetParameter3fv(cameraPosition, camPos);
	OpenGLRenderer::checkForCgError("setting camera position");
}

void MultPerPixelLightFS::UpdateMatrixModelWorld(float* matModWorld)
{
	cgSetMatrixParameterfr(matrixModelWorld, matModWorld);
	OpenGLRenderer::checkForCgError("setting invWorldObj matrix");
}