/****************************************************************
 * Base shader class holding shared Cg code between all shaders	*
 ****************************************************************/

#pragma once
#include "GL\glut.h"
#include "Cg\cg.h"
#include "Cg\cgGL.h"

class ProgramCg
{
public:
	ProgramCg();
	ProgramCg(char* fileName, char* programName, CGprofile& profile);	//pass in shader file name, shader function name, and shader type
	virtual ~ProgramCg();

protected:
	static void InitContext();
	static void CheckForCgError(const char *situation);
	static CGcontext cgContext;
	static bool contextReady;

	CGprogram program;
};

