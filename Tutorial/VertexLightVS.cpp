#include "stdafx.h"
#include "VertexLightVS.h"
#include "OpenGLRenderer.h"

VertexLightVS::VertexLightVS()
{
}


VertexLightVS::~VertexLightVS()
{
}

void VertexLightVS::LinkParameters()
{
	matrixModelWorld = cgGetNamedParameter(vertexProgram, "matrixModelWorld");
	OpenGLRenderer::checkForCgError("could not get matrixModelWorld parameter");

	matrixViewProj = cgGetNamedParameter(vertexProgram, "matrixViewProj");
	OpenGLRenderer::checkForCgError("could not get matrixViewProj parameter");

	modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");

	lightPosition = cgGetNamedParameter(vertexProgram, "lightPosition");
	OpenGLRenderer::checkForCgError("could not get lightPosition parameter");
}

void VertexLightVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(modelViewProj, MVP);
	OpenGLRenderer::checkForCgError("setting model view projection matrix");
}

void VertexLightVS::UpdateMatrixModelWorld(float* MVP)
{
	cgSetMatrixParameterfr(matrixModelWorld, MVP);
	OpenGLRenderer::checkForCgError("setting model to world matrix");
}

void VertexLightVS::UpdateMatrixViewProj(float* MVP)
{
	cgSetMatrixParameterfr(matrixViewProj, MVP);
	OpenGLRenderer::checkForCgError("setting view projection matrix");
}

void VertexLightVS::UpdateLightPosition(float* lightPos)
{
	cgGLSetParameter3fv(lightPosition, lightPos);
	OpenGLRenderer::checkForCgError("setting light position");
}