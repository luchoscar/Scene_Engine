/********************************
 * Holds game logic and objects	*
 ********************************/

#pragma once
#include "BaseObject.h"
//#include <GL/glew.h>
//#include <GL/wglew.h>
#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include <vector>
#include <time.h> 
#include "OpenGLRenderer.h"

using namespace std;

#include "SimpleVS.h"

class Scene
{
public:
	static float deltaTime;

	Scene();
	virtual ~Scene();
	
	virtual void Init();
	virtual void Draw();
	virtual void Update();

protected:
	clock_t t;	//used to calculate delta time
	vector<BaseObject*> list;

	OpenGLRenderer rendererGL;

	//shader variables
	CGcontext myCgContext;

	CGprofile myCgVertexProfile,
				myCgFragmentProfile;

	//first shader
	CGprogram   myCgVertexProgram,
				myCgFragmentProgram;

	CGparameter myCgVertexParam_modelViewProj,
				myCgFragmentParam_c;

	void checkForCgError(const char *situation);

	SimpleVS simpleVS;
};
