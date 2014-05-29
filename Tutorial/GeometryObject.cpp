#include "stdafx.h"
#include "GeometryObject.h"
#include "OpenGLRenderer.h"

GeometryObject::GeometryObject()
{
}


GeometryObject::~GeometryObject()
{
}

void GeometryObject::CreateProgram(const char* fileName, const char* functionName)
{
	geometryProgram = cgCreateProgramFromFile(
		OpenGLRenderer::GetContext(),
		CG_SOURCE,
		fileName, //File name of shader program
		OpenGLRenderer::GetGeometryProfile(),
		functionName, //Entry function
		NULL);

	OpenGLRenderer::checkForCgError("Creating geometry program from file");
}

CGprogram GeometryObject::GetProgram()
{
	return geometryProgram;
}

void GeometryObject::UpdateParameters()
{
	cgUpdateProgramParameters(geometryProgram);
}
