#pragma once

#include "StdAfx.h"
#include <iostream>
#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include <vector>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	int setTextureinList(const char* texturePath);
	const char* setTextureinMap(const char* texturePath);

	GLuint getTextureId(const char* texturePath); 
	GLuint getTextureId(int idx);
	

private:
	int textureCount;
	std::map<const char*, GLuint> textureDic;
	std::vector<GLuint> textureIds;
};

