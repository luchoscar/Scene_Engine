#pragma once
#include "VertexObject.h"

class SimpleVS : VertexObject
{
public:
	SimpleVS();
	~SimpleVS();

	virtual void InitShader(const char* fileName, const char* programName);
};

