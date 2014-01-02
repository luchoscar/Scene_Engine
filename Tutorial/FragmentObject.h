#pragma once

#include <GL\glut.h>
#include <CG\cg.h>

#include <CG\cgGL.h>
class FragmentObject
{
public:
	FragmentObject();
	virtual ~FragmentObject();

	void CreateProgram(const char* fileName, const char* functionName);
	CGprogram GetProgram() { return fragmentProgram; };

	virtual void LinkParameters() = 0;
	virtual void UpdateParameters() = 0;

protected:
	CGprogram fragmentProgram;
};

