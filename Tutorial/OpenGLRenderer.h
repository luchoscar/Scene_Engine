#pragma once

#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>

class OpenGLRenderer
{
public:
	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	static void Init();

protected:
	static CGcontext myCgContext;
	static void InitContext();
	static void checkForCgError(const char *situation);

private:
	static bool contextInitialized;

};

