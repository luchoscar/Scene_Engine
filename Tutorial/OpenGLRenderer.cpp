#include "StdAfx.h"
#include "OpenGLRenderer.h"
#include <iostream>

bool OpenGLRenderer::contextInitialized = false;
CGcontext OpenGLRenderer::myCgContext;

OpenGLRenderer::OpenGLRenderer()
{

}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::InitContext()
{
	if (OpenGLRenderer::contextInitialized) return;
	
	myCgContext = cgCreateContext();
	checkForCgError("creating context");
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

	OpenGLRenderer::contextInitialized = true;
}

void OpenGLRenderer::checkForCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		printf("%s: %s: %s\n",
			"OpenGLVer2", situation, string);
		if (error == CG_COMPILER_ERROR) 
		{
			printf("%s\n", cgGetLastListing(myCgContext));
		}
		
		char x;
		std::cin >> x;

		exit(1);
	}
}
