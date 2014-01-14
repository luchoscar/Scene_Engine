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
	modelViewProj = cgGetNamedParameter(vertexProgram, "modelViewProj");
	OpenGLRenderer::checkForCgError("could not get modelViewProj parameter");
}

void SimpleVS::UpdateModelViewMatrix(float* MVP)
{
	cgSetMatrixParameterfr(modelViewProj, MVP);
}