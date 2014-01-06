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

	void UpdateModelViewMatrix(float* MVP) { cgSetMatrixParameterfr(vertexParam_modelViewProj, MVP); };
	CGparameter GetModelViewProjMatrix() { return vertexParam_modelViewProj; };

	virtual void LinkParameters() = 0;
	void UpdateParameters() { cgUpdateProgramParameters(vertexProgram); };
protected:
	CGprogram vertexProgram;

	CGparameter vertexParam_modelViewProj;
};

