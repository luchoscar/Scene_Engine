/********************************
 * Holds game logic and objects	*
 ********************************/

#pragma once
#include "BaseObject.h"
#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include <vector>

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	
	virtual void Init();
	virtual void Draw();
	virtual void Update();

protected:
	vector<BaseObject*> list;

	//shader variables
	CGcontext myCgContext;

	CGprofile myCgVertexProfile,
				myCgFragmentProfile;

	CGprogram   myCgVertexProgram,
				myCgFragmentProgram;

	CGparameter myCgVertexParam_modelViewProj,
				myCgFragmentParam_c;

	void checkForCgError(const char *situation);
};
