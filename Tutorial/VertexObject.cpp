#include "StdAfx.h"
#include "VertexObject.h"
#include "OpenGLRenderer.h"

VertexObject::VertexObject()
{
}


VertexObject::~VertexObject()
{
}

void VertexObject::CreateProgram(const char* fileName, const char* functionName)
{
	vertexProgram = cgCreateProgramFromFile(
		OpenGLRenderer::GetContext(),
		CG_SOURCE, 
		fileName, //File name of shader program
		OpenGLRenderer::GetVertexProfile(),
		functionName, //Entry function
		NULL);

	OpenGLRenderer::checkForCgError("Creating program from file");
}