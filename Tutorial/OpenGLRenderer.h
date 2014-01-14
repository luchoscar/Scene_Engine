#pragma once

#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include "TextureManager.h"

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	void LoadProgram(CGprogram program);
	static void InitContext();
	static void InitVertexProfile();
	static void InitFragmentProfile();
	static CGcontext GetContext() { return myCgContext; };
	static CGprofile GetVertexProfile() { return vertexProfile; };
	static CGprofile GetFragmentProfile() { return fragmentProfile; };
	static void ClearGLFlags();
	static void BindProgram(CGprogram _program);
	static void EnableProfile(CGprofile _profile);
	static void DisableProfile(CGprofile _profile);
	static void checkForCgError(const char *situation);
	
protected:
	static CGcontext myCgContext;
	static CGprofile vertexProfile,
				fragmentProfile;

private:
	static bool contextInitialized;
	static bool vertexProfileInitialized;
	static bool fragmentProfileInitialized;
};

