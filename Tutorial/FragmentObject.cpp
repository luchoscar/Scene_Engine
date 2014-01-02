#include "StdAfx.h"
#include "FragmentObject.h"
#include "OpenGLRenderer.h"

FragmentObject::FragmentObject()
{
}


FragmentObject::~FragmentObject()
{
}

void FragmentObject::CreateProgram(const char* fileName, const char* functionName)
{
	fragmentProgram = cgCreateProgramFromFile(
		OpenGLRenderer::GetContext(),
		CG_SOURCE, 
		fileName, //File name of shader program
		OpenGLRenderer::GetFragmentProfile(),
		functionName, //Entry function
		NULL);

	OpenGLRenderer::checkForCgError("Creating fragment program from file");
}