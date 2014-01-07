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