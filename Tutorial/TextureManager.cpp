#include "stdafx.h"
#include "TextureManager.h"
#include "..\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "..\\Simple OpenGL Image Library\\projects\\VC9\\Debug\\SOIL.lib")

TextureManager::TextureManager()
{
	textureCount = -1;
}


TextureManager::~TextureManager()
{
}

GLuint TextureManager::getTextureId(int idx)
{
	if (idx > textureCount + 1)
		std::cout << "Idx greater than textureIds vector" << std::endl;

	return textureIds[idx];
}

GLuint TextureManager::getTextureId(const char* texturePath)
{
	if (textureDic.find(texturePath) == textureDic.end())
		std::cout << "Key is not in texture dictionary" << std::endl;

	return textureDic[texturePath];
}

//Set texture id in memory and return index on texture list
int TextureManager::setTextureinList(const char* texturePath)
{
	GLuint textId = SOIL_load_OGL_texture
		(
		texturePath,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	
	textureIds.push_back(textId);
	
	return ++textureCount;
}

const char* TextureManager::setTextureinMap(const char* texturePath)
{
	if (textureDic.find(texturePath) != textureDic.end())
	{
		GLuint textId = SOIL_load_OGL_texture
			(
			texturePath,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);

		textureDic.insert(std::pair<const char*, GLuint>(texturePath, textId));
	}

	return texturePath;
}