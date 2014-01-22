#pragma once

#include <CG\cg.h>
#include <CG\cgGL.h>

class VertexObject
{
public:
	VertexObject();
	virtual ~VertexObject();

	void CreateProgram(const char* fileName, const char* functionName);
	CGprogram GetProgram();
	void UpdateParameters();

	virtual void LinkParameters() = 0;

protected:
	CGprogram vertexProgram;
};