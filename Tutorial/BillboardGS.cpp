#include "stdafx.h"
#include "BillboardGS.h"
#include "OpenGLRenderer.h"

BillboardGS::BillboardGS()
{
}


BillboardGS::~BillboardGS()
{
}

void BillboardGS::UpdateCameraPosition(float* camPos)
{
	cgGLSetParameter3fv(cameraPosition, camPos);
	OpenGLRenderer::checkForCgError("setting cameraPosition");
}

void BillboardGS::UpdateBillboardSize(float size)
{
	cgGLSetParameter1f(billboardSize, size);
	OpenGLRenderer::checkForCgError("setting billboardSize");
}

void BillboardGS::UpdateMatrixMVP(float* MWVP)
{
	cgSetMatrixParameterfr(matrixMVP, MWVP);
	OpenGLRenderer::checkForCgError("setting MWVP matrix");
}

void BillboardGS::LinkParameters() 
{
	cameraPosition = cgGetNamedParameter(geometryProgram, "cameraPosition");
	OpenGLRenderer::checkForCgError("could not get cameraPosition parameter");

	billboardSize = cgGetNamedParameter(geometryProgram, "billboardSize");
	OpenGLRenderer::checkForCgError("could not get bitangent parameter");

	matrixMVP = cgGetNamedParameter(geometryProgram, "matrixMVP");
	OpenGLRenderer::checkForCgError("could not get matrixMVP parameter");
}