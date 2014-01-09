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
#include "OpenGLRenderer.h"

using namespace std;

#include "SimpleVS.h"
#include "SimpleFS.h"
#include "TextureFS.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	
	virtual void Init();
	virtual void Draw();
	virtual void Update();

protected:
	//List holding all objects in scene
	vector<BaseObject*> list;
	
	//object holding OpenGL code
	OpenGLRenderer rendererGL;

	//shader variables
	CGcontext myCgContext;

	CGprofile myCgVertexProfile,
				myCgFragmentProfile;

	//first shader
	CGprogram   myCgVertexProgram,
				myCgFragmentProgram;

	void checkForCgError(const char *situation);

	SimpleVS simpleVS;
	//SimpleFS simpleFS;
	TextureFS simpleFS;
	TextureFS textureFS;
};
