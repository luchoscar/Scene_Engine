#include "stdafx.h"
#include "PixelLightVS.h"
#include "OpenGLRenderer.h"

PixelLightVS::PixelLightVS()
{
}


PixelLightVS::~PixelLightVS()
{
}

void PixelLightVS::LinkParameters()
{
	modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");

	inverseModelToWorld = cgGetNamedParameter(vertexProgram, "inverseModelToWorld");
	OpenGLRenderer::checkForCgError("could not get inverseModelToWorld parameter");

	lightPosition = cgGetNamedParameter(vertexProgram, "lightPosition");
	OpenGLRenderer::checkForCgError("could not get lightPosition parameter");

	cameraPosition = cgGetNamedParameter(vertexProgram, "cameraPosition");
	OpenGLRenderer::checkForCgError("could not get eyePos parameter");
}

void PixelLightVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(modelViewProj, MVP);
}

void PixelLightVS::UpdateInverseModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(inverseModelToWorld, MVP);
}

void PixelLightVS::UpdateLightPosition(float* lightPos)
{
	cgGLSetParameter3fv(lightPosition, lightPos);
}

void PixelLightVS::UpdateCameraPosition(float* camPos)
{
	cgGLSetParameter3fv(cameraPosition, camPos);
}