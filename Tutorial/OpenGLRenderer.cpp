#include "StdAfx.h"
#include "OpenGLRenderer.h"
#include <iostream>

bool OpenGLRenderer::contextInitialized = false;
bool OpenGLRenderer::vertexProfileInitialized = false;
bool OpenGLRenderer::fragmentProfileInitialized = false;

CGcontext OpenGLRenderer::myCgContext;
CGprofile OpenGLRenderer::vertexProfile;
CGprofile OpenGLRenderer::fragmentProfile;

OpenGLRenderer::OpenGLRenderer()
{
	OpenGLRenderer::contextInitialized = false;
}

OpenGLRenderer::~OpenGLRenderer()
{
}

// Initializing OpenGL context, seting OpenGL flags and flag to only allow for one context
void OpenGLRenderer::InitContext()
{
	if (OpenGLRenderer::contextInitialized) return;
	
	myCgContext = cgCreateContext();
	checkForCgError("creating context");
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

	glEnable(GL_DEPTH_TEST); 

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);

	OpenGLRenderer::contextInitialized = true;
}

//Initialize vertex profile and setting flag to only one profile
void OpenGLRenderer::InitVertexProfile()
{
	if (vertexProfileInitialized) return;

	vertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(vertexProfile);
	checkForCgError("selecting vertex profile");

	vertexProfileInitialized = true;
}

//Initialize fragment profile and setting flag to only one profile
void OpenGLRenderer::InitFragmentProfile()
{
	if (fragmentProfileInitialized) return;

	fragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(fragmentProfile);
	checkForCgError("selecting fragment profile");

	fragmentProfileInitialized = true;
}

void OpenGLRenderer::LoadProgram(CGprogram program)
{
	cgGLLoadProgram(program);
	checkForCgError("Loading program");
}

//Clear depth and color buffers
void OpenGLRenderer::ClearGLFlags()
{
	glClearColor(0.6, 0.3, 0.25, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::BindProgram(CGprogram _program)
{
	cgGLBindProgram(_program);
	checkForCgError("Binding program");
}

void OpenGLRenderer::EnableProfile(CGprofile _profile)
{
	cgGLEnableProfile(_profile);
	checkForCgError("Enabling profile");
}

void OpenGLRenderer::DisableProfile(CGprofile _profile)
{
	cgGLDisableProfile(_profile);
}

void OpenGLRenderer::EnableTexture(CGparameter texture)
{
	cgGLEnableTextureParameter(texture);
	OpenGLRenderer::checkForCgError("enable texture");
}

//Capture compiler error and displays it on screen
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
		x << std::cin.get();

		exit(1);
	}
}