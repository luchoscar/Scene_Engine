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

	modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");

	lightPosition = cgGetNamedParameter(vertexProgram, "lightPosition");
	OpenGLRenderer::checkForCgError("could not get lightPosition parameter");
}

void PerPixelLightVS::UpdateTangent(float* tan)
{
	cgGLSetParameter3fv(lightPosition, tan);
	OpenGLRenderer::checkForCgError("setting tangent");
}

void PerPixelLightVS::UpdateBitangent(float* bitan)
{
	cgGLSetParameter3fv(lightPosition, bitan);
	OpenGLRenderer::checkForCgError("setting bitangent");
}

void PerPixelLightVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(modelViewProj, MVP);
	OpenGLRenderer::checkForCgError("setting model view projection matrix");
}

void PerPixelLightVS::UpdateMatrixModelWorld(float* MVP)
{
	cgSetMatrixParameterfr(matrixModelWorld, MVP);
	OpenGLRenderer::checkForCgError("setting model to world matrix");
}

void PerPixelLightVS::UpdateMatrixViewProj(float* MVP)
{
	cgSetMatrixParameterfr(matrixViewProj, MVP);
	OpenGLRenderer::checkForCgError("setting view projection matrix");
}

void PerPixelLightVS::UpdateLightPosition(float* lightPos)
{
	cgGLSetParameter3fv(lightPosition, lightPos);
	OpenGLRenderer::checkForCgError("setting light position");
}
