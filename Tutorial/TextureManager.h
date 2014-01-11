#pragma once

#include "StdAfx.h"
#include <iostream>
#include <GL\glut.h>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include <vector>
#include <map>
#include "wBitmap.h"

class TextureManager
{
public:
	TextureManager();
	TextureManager(int totalTextures);
	~TextureManager();

	void Init(int In_textures);
	void setBmpTextureinMap(char* texturePath);
	
	GLuint getTextureId(const char* texturePath); 

private:
	int textureCount;
	std::map<const char*, GLuint> textureDic;
	//std::vector<GLuint> textureIds;

	int totalTextures;
	GLuint* texturesIds;
	wBitmap* bitmap;
	int textureCounter;

	void FreeMemory();
};

