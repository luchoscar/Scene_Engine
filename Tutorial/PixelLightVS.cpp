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
	matrixModelWorld = cgGetNamedParameter(vertexProgram, "matrixModelWorld");
	OpenGLRenderer::checkForCgError("could not get matrixModelWorld parameter");

	matrixViewProj = cgGetNamedParameter(vertexProgram, "matrixViewProj");
	OpenGLRenderer::checkForCgError("could not get matrixViewProj parameter");

	modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");

	lightPosition = cgGetNamedParameter(vertexProgram, "lightPosition");
	OpenGLRenderer::checkForCgError("could not get lightPosition parameter");
	
	//inverseModelToWorld = cgGetNamedParameter(vertexProgram, "inverseModelToWorld");
	//OpenGLRenderer::checkForCgError("could not get inverseModelToWorld parameter");
	
	//cameraPosition = cgGetNamedParameter(vertexProgram, "cameraPosition");
	//OpenGLRenderer::checkForCgError("could not get eyePos parameter");
}

void PixelLightVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(modelViewProj, MVP);
}

void PixelLightVS::UpdateMatrixModelWorld(float* MVP)
{
	cgSetMatrixParameterfr(matrixModelWorld, MVP);
}

void PixelLightVS::UpdateMatrixViewProj(float* MVP)
{
	cgSetMatrixParameterfr(matrixViewProj, MVP);
}

void PixelLightVS::UpdateLightPosition(float* lightPos)
{
	cgGLSetParameter3fv(lightPosition, lightPos);
}

//void PixelLightVS::UpdateInverseModelViewMatrix(float* MVP)
//{
//	cgSetMatrixParameterfr(inverseModelToWorld, MVP);
//}
//
//
//void PixelLightVS::UpdateCameraPosition(float* camPos)
//{
//	cgGLSetParameter3fv(cameraPosition, camPos);
//}