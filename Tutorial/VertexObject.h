#pragma once

#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>

class VertexObject
{
public:
	VertexObject();
	virtual ~VertexObject();

	void CreateProgram(const char* fileName, const char* functionName);
	CGprogram GetProgram() { return vertexProgram; };

	virtual void UpdateParameters() = 0;

protected:
	CGprogram vertexProgram;
};

