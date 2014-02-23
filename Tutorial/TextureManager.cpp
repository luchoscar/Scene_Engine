#include "stdafx.h"
#include "TextureManager.h"
#include "OpenGLRenderer.h"

#include "..\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "..\\Simple OpenGL Image Library\\projects\\VC9\\Debug\\SOIL.lib")

TextureManager::TextureManager()
{
	textureCount = -1;
}

TextureManager::TextureManager(int In_totalTextures)
{
	Init(In_totalTextures);
}

//Initialize all texturesIds for scene
void TextureManager::Init(int In_textures)
{
	FreeMemory();

	totalTextures = In_textures;
	texturesIds = new GLuint[totalTextures];

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /* Tightly packed texture data. */

	glGenTextures(totalTextures, texturesIds);
	textureCounter = -1;
}

TextureManager::~TextureManager()
{
	FreeMemory();
}

//Delete textureId pointers
void TextureManager::FreeMemory()
{
	textureDic.clear();
	
	if (textureCounter > -1)
		delete(texturesIds);
}

//Retrieve textureId from map / hash table
GLuint TextureManager::getTextureId(const char* texturePath)
{
	if (textureDic.find(texturePath) == textureDic.end())
		std::cout << "Key is not in texture dictionary" << std::endl;

	GLuint textId = textureDic[texturePath];
	return textId;
}

//Set bitmap to textireId if file is not already in textureId map / hash table
void TextureManager::setBmpTextureinMap(char* texturePath)
{
	if (textureDic.find(texturePath) == textureDic.end())
	{
		bitmap = wLoadBitmap(texturePath);
		
		textureCounter++;
		glBindTexture(GL_TEXTURE_2D, texturesIds[textureCounter]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		wFreeBitmap(bitmap);

		textureDic.insert(std::pair<const char*, GLuint>(texturePath, texturesIds[textureCounter]));
	}
	else
		std::cout << "Texture already in map" << std::endl;
}

///*** code to read a .bmp image *****************************************************/

#include <math.h>

#define	MAX_EXP 14

int power(int base, int exp) {
	int val, i;

	if (exp == 0)
		return 1;

	val = base;
	for (i = 1; i < exp; i++) {
		val *= base;
	}
	return val;
}

// returns a pointer to the loaded bitmap
// only supports 24-bit (and 32-bit?) images
wBitmap* wLoadBitmap(char *filename)
{
	FILE *bmpFile;
	wBitmap *bmp;
	int i;
	int fileLineSize, memLineSize, fileScanLines, memScanLines, dataSize;
	int pad, generic;
	BYTE *line;

	bmp = (wBitmap*)malloc(sizeof(wBitmap));
	memset(bmp, 0, sizeof(wBitmap));
	bmp->name = filename;

	bmpFile = fopen(filename, "rb");
	if (bmpFile)
	{
		printf("Loading bitmap %s\n", filename);

		fread(&bmp->Header, sizeof(bmp->Header), 1, bmpFile);
		fread(&bmp->Info, sizeof(bmp->Info), 1, bmpFile);

		// only supports 24-bit+ color bitmaps
		if (bmp->Info.biBitCount < 24)
		{
			printf("cannot load %s:  bitmap is less than 24-bit color\n", filename);
			free(bmp);
			return NULL;
		}
		if (bmp->Info.biCompression)
		{
			printf("cannot load %s:  bitmap is compressed\n", filename);
			free(bmp);
			return NULL;
		}

		fileLineSize = bmp->Info.biWidth*bmp->Info.biBitCount / 8;
		pad = 4 - fileLineSize % 4;
		if (pad == 4)
			pad = 0;
		fileScanLines = bmp->Info.biHeight;

		// check to make sure that image is 2^x * 2^y
		// image in memory can be 2^x * 2^y even if disk file isn't, but there will be blank pixels
		for (i = 1; i <= MAX_EXP; i++)
		{
			generic = (int)power(2, i);
			if (generic >= bmp->Info.biWidth)
			{
				bmp->Info.biWidth = generic;
				break;
			}
		}
		if (i > MAX_EXP)
		{
			printf("cannot load %s:  bitmap is too large\n", filename);
			free(bmp);
			return NULL;
		}
		for (i = 1; i <= MAX_EXP; i++)
		{
			generic = power(2, i);
			if (generic >= bmp->Info.biHeight)
			{
				bmp->Info.biHeight = generic;
				break;
			}
		}
		if (i > MAX_EXP)
		{
			printf("cannot load %s:  bitmap is too large\n", filename);
			free(bmp);
			return NULL;
		}

		memLineSize = bmp->Info.biWidth*bmp->Info.biBitCount / 8;
		memScanLines = bmp->Info.biHeight;
		dataSize = memLineSize*memScanLines;
		bmp->pixels = (BYTE*)malloc(dataSize);
		memset(bmp->pixels, 0, dataSize);

		// end 2^n check
		/*		printf("image is %i by %i", fileLineSize*8/bmp->Info.biBitCount, fileScanLines);
		if ( fileLineSize != memLineSize || fileScanLines != memScanLines )
		printf(", expanded to %i by %i", memLineSize*8/bmp->Info.biBitCount, memScanLines);
		printf("\n");
		*/

		// bmps are stored last line first
		fseek(bmpFile, bmp->Header.bfOffBits, 0);
		line = bmp->pixels + (fileScanLines - 1)*memLineSize;
		for (i = 0; i < fileScanLines; i++)
		{
			fread(line, fileLineSize, 1, bmpFile);
			// lines are padded to be 32-bit divisible
			if (pad)
				fread(&generic, pad, 1, bmpFile);
			line -= memLineSize;
		}

		// need to switch red and blue for opengl
		if (TRUE)
		{
			for (i = 0; i < fileScanLines*memLineSize; i += 3)
			{
				generic = bmp->pixels[i];
				bmp->pixels[i] = bmp->pixels[i + 2];
				bmp->pixels[i + 2] = generic;
			}
		}
		return bmp;
	}
	else
	{
		printf("cannot load %s:  no such file or file I/O error\n", filename);
		return NULL;
	}
}

void wSaveBitmap(char *filename, wBitmap *bmp)
{
	FILE *bmpFile;
	int i, LineSize, ScanLines, pad, generic = 0;
	BYTE *line;

	if (!bmp)
	{
		printf("Error: cannot write null bitmap to file \"%s\"\n", filename);
		return;
	}

	bmpFile = fopen(filename, "wb");
	if (bmpFile)
	{
		fwrite(&bmp->Header, sizeof(bmp->Header), 1, bmpFile);
		fwrite(&bmp->Info, sizeof(bmp->Info), 1, bmpFile);

		LineSize = bmp->Info.biWidth*bmp->Info.biBitCount / 8;
		pad = 4 - LineSize % 4;
		if (pad == 4)
			pad = 0;
		ScanLines = bmp->Info.biHeight;
		line = bmp->pixels + (ScanLines - 1)*LineSize;
		for (i = 0; i < ScanLines; i++) {
			fwrite(line, LineSize, 1, bmpFile);
			if (pad)
				fwrite(&generic, pad, 1, bmpFile);
			line -= LineSize;
		}
		fclose(bmpFile);
	}
	else
	{
		printf("cannot open bitmap file for writing");
	}
}

void wFreeBitmap(wBitmap* bitmap)
{
	free(bitmap->pixels);
	free(bitmap);
}