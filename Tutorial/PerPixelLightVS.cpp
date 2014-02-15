#include "stdafx.h"
#include "PerPixelLightVS.h"
#include "OpenGLRenderer.h"

PerPixelLightVS::PerPixelLightVS()
{
}


PerPixelLightVS::~PerPixelLightVS()
{
}

void PerPixelLightVS::LinkParameters()
{
	tangent = cgGetNamedParameter(vertexProgram, "tangent");
	OpenGLRenderer::checkForCgError("could not get tangent parameter");

	bitangent = cgGetNamedParameter(vertexProgram, "bitangent");
	OpenGLRenderer::checkForCgError("could not get bitangent parameter");

	matrixModelWorld = cgGetNamedParameter(vertexProgram, "matrixModelWorld");
	OpenGLRenderer::checkForCgError("could not get matrixModelWorld parameter");

	matrixViewProj = cgGetNamedParameter(vertexProgram, "matrixViewProj");
	OpenGLRenderer::checkForCgError("could not get matrixViewProj parameter");

	lightPosition = cgGetNamedParameter(vertexProgram, "lightPosition");
	OpenGLRenderer::checkForCgError("could not get lightPosition parameter");

	cameraPosition = cgGetNamedParameter(vertexProgram, "cameraPosition");
	OpenGLRenderer::checkForCgError("could not get cameraPosition parameter");
}

void PerPixelLightVS::UpdateTangent(float* tan)
{
	cgGLSetParameter3fv(tangent, tan);
	OpenGLRenderer::checkForCgError("setting tangent");
}

void PerPixelLightVS::UpdateBitangent(float* bitan)
{
	cgGLSetParameter3fv(bitangent, bitan);
	OpenGLRenderer::checkForCgError("setting bitangent");
}

void PerPixelLightVS::UpdateMatrixModelWorld(float* World)
{
	cgSetMatrixParameterfr(matrixModelWorld, World);
	OpenGLRenderer::checkForCgError("setting model to world matrix");
}

void PerPixelLightVS::UpdateMatrixViewProj(float* ViewProj)
{
	cgSetMatrixParameterfr(matrixViewProj, ViewProj);
	OpenGLRenderer::checkForCgError("setting view projection matrix");
}

void PerPixelLightVS::UpdateLightPosition(float* lightPos)
{
	cgGLSetParameter3fv(lightPosition, lightPos);
	OpenGLRenderer::checkForCgError("setting light position");
}

void PerPixelLightVS::UpdateCameraPosition(float* camPos)
{
	cgGLSetParameter3fv(cameraPosition, camPos);
	OpenGLRenderer::checkForCgError("setting camera position");
}