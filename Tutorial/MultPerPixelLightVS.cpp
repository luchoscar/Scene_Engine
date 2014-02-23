#include "stdafx.h"
#include "MultPerPixelLightVS.h"
#include "OpenGLRenderer.h"

MultPerPixelLightVS::MultPerPixelLightVS()
{
}


MultPerPixelLightVS::~MultPerPixelLightVS()
{
}

void MultPerPixelLightVS::LinkParameters()
{
	tangent = cgGetNamedParameter(vertexProgram, "tangent");
	OpenGLRenderer::checkForCgError("could not get tangent parameter");

	bitangent = cgGetNamedParameter(vertexProgram, "bitangent");
	OpenGLRenderer::checkForCgError("could not get bitangent parameter");

	matrixModelWorld = cgGetNamedParameter(vertexProgram, "matrixModelWorld");
	OpenGLRenderer::checkForCgError("could not get matrixModelWorld parameter");

	matrixViewProj = cgGetNamedParameter(vertexProgram, "matrixViewProj");
	OpenGLRenderer::checkForCgError("could not get matrixViewProj parameter");

	cameraPosition = cgGetNamedParameter(vertexProgram, "cameraPosition");
	OpenGLRenderer::checkForCgError("could not get cameraPosition parameter");
}

void MultPerPixelLightVS::UpdateTangent(float* tan)
{
	cgGLSetParameter3fv(tangent, tan);
	OpenGLRenderer::checkForCgError("setting tangent");
}

void MultPerPixelLightVS::UpdateBitangent(float* bitan)
{
	cgGLSetParameter3fv(bitangent, bitan);
	OpenGLRenderer::checkForCgError("setting bitangent");
}

void MultPerPixelLightVS::UpdateMatrixModelWorld(float* World)
{
	cgSetMatrixParameterfr(matrixModelWorld, World);
	OpenGLRenderer::checkForCgError("setting model to world matrix");
}

void MultPerPixelLightVS::UpdateMatrixViewProj(float* ViewProj)
{
	cgSetMatrixParameterfr(matrixViewProj, ViewProj);
	OpenGLRenderer::checkForCgError("setting view projection matrix");
}

void MultPerPixelLightVS::UpdateCameraPosition(float* camPos)
{
	cgGLSetParameter3fv(cameraPosition, camPos);
	OpenGLRenderer::checkForCgError("setting camera position");
}