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
