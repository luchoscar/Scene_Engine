#include "StdAfx.h"
#include "SimpleVS.h"
#include "OpenGLRenderer.h"

SimpleVS::SimpleVS() : VertexObject()
{
}


SimpleVS::~SimpleVS()
{
}

void SimpleVS::LinkParameters()
{
	vertexParam_modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");
}

void SimpleVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(vertexParam_modelViewProj, MVP);
}

void SimpleVS::UpdateParameters()
{
	cgUpdateProgramParameters(vertexProgram);
}
