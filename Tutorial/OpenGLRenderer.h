#pragma once

#include "stdafx.h"
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
	static void InitGeometryProfile();

	static CGcontext GetContext() { return myCgContext; };
	static CGprofile GetVertexProfile() { return vertexProfile; };
	static CGprofile GetFragmentProfile() { return fragmentProfile; };
	static CGprofile GetGeometryProfile() { return geometryProfile; };

	static void ClearGLFlags();
	static void BindProgram(CGprogram _program);
	static void EnableProfile(CGprofile _profile);
	static void DisableProfile(CGprofile _profile);
	static void EnableTexture(CGparameter texture);
	static void EnableAlphaBlending();
	static void DisableAlphaBlending();
	static void EnableFaceCulling();
	static void DisableFaceCulling();
	static void EnableDepthTest();
	static void DisableDepthTest();

	static CGparameter BindCgParameter(CGprogram program, const char* paramName);
	static void UpdateFloatParameter(CGparameter& parameter, float value, const char* paramName);
	static void UpdateMatrixParameter(CGparameter& parameter, float* value, const char* paramName);
	static void UpdateVector3dParameter(CGparameter& parameter, float* value, const char* paramName);
	static void UpdateVectorTexture2dParameter(CGparameter& parameter, GLuint textureParam, const char* paramName);

	static void checkForCgError(const char *situation);
	static void checkForCgError(const char *situation, const char *parameter);
	//static void 
protected:
	static CGcontext myCgContext;
	static CGprofile vertexProfile,
						fragmentProfile,
						geometryProfile;
private:
	static bool contextInitialized;
	static bool vertexProfileInitialized;
	static bool fragmentProfileInitialized;
	static bool geometryProfileInitialized;
};

