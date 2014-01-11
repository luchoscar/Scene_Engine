#include "stdafx.h"
#include "TextureFS.h"
#include "OpenGLRenderer.h"

TextureFS::TextureFS()
{
}


TextureFS::~TextureFS()
{
}

void TextureFS::LinkParameters()
{
	decalMap = cgGetNamedParameter(fragmentProgram, "decalMap");
	OpenGLRenderer::checkForCgError("could not get decalMap parameter");
}

void TextureFS::SetTextureParameter(GLuint textureParam)
{ 
	/*cgGLEnableTextureParameter(decalMap);
	OpenGLRenderer::checkForCgError("cannot enable decal texture");

	cgGLSetTextureParameter(decalMap, textureParam); 
	OpenGLRenderer::checkForCgError("could not set decalMap parameter");
*/
	cgGLEnableTextureParameter(decalMap);
	OpenGLRenderer::checkForCgError("enable decal texture");

	cgGLSetTextureParameter(decalMap, textureParam);
	OpenGLRenderer::checkForCgError("setting decal 2D texture");
}