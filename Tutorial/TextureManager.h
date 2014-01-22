#pragma once

#include "StdAfx.h"
#include <iostream>
#include <CG\cg.h>
#include <CG\cgGL.h>
#include <vector>
#include <map>
#include "wBitmap.h"

#include "..\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "..\\Simple OpenGL Image Library\\projects\\VC9\\Debug\\SOIL.lib")

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

	int totalTextures;
	GLuint* texturesIds;
	wBitmap* bitmap;
	int textureCounter;

	void FreeMemory();
};

