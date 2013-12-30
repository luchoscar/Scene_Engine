#pragma once

class VertexObject
{
public:
	VertexObject();
	virtual ~VertexObject();

	virtual void InitShader(const char* fileName, const char* programName) = 0;

protected:
};

