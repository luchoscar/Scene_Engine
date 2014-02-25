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

	matrixMVP = cgGetNamedParameter(vertexProgram, "matrixMVP");
	OpenGLRenderer::checkForCgError("could not get matrixMVP parameter");
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

void MultPerPixelLightVS::UpdateMatrixMVP(float* MWVP)
{
	cgSetMatrixParameterfr(matrixMVP, MWVP);
	OpenGLRenderer::checkForCgError("setting MWVP matrix");
}