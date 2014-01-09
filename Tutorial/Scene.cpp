/****************************************************************************
 * Scene to control game logic - evenually to be made into a hierarchy		*
 * in order to implement a Vector<SceneBase> from Engine.cpp				*
 * Logic to create, enable and disable VS & FS to be moved to its own		*
 * hierarchy system															*
 * Camera to be set as its own derviced class from BaseObject				*
 ****************************************************************************/

#include "StdAfx.h"
#include "Scene.h"
#include "ObjectTriangle.h"
#include "ObjectCube.h"
#include "Matrix3D.h"
#include "Engine.h"
#include <iostream>
#include "wBitmap.h"

//SOIL Image library - SOIL commands to be moved to OpenGLRenderer class
#include "..\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "..\\Simple OpenGL Image Library\\projects\\VC9\\Debug\\SOIL.lib")

Scene::Scene(void)
{

}

Scene::~Scene(void)
{
	//Delete all objects in list
	for (unsigned int i=0; i<list.size(); i++)
	{
		delete list[i];
	}

	list.clear();
}

const int numTextures = 2;
char *textureFileName[numTextures];
GLuint textureId[numTextures];

//initializing scene
void Scene::Init()
{
	//create OpenGL context
	rendererGL.InitContext();

	//creating VS profile
	rendererGL.InitVertexProfile();

	//creating FS profile
	rendererGL.InitFragmentProfile();

	//creating VS program
	simpleVS.CreateProgram("vertex_shader.cg", "VS_program");
	rendererGL.LoadProgram(simpleVS.GetProgram());
	simpleVS.LinkParameters();

	//creating FS program
	simpleFS.CreateProgram("fragment_shader.cg", "FS_program");
	rendererGL.LoadProgram(simpleFS.GetProgram());
	simpleFS.LinkParameters();
	
	//create FS program
	textureFS.CreateProgram("textureFragment.cg", "FS_program");
	rendererGL.LoadProgram(textureFS.GetProgram());
	textureFS.LinkParameters();
	
	//testing SOIL - need to change float[3] tp float[5] so vertices store UV coordinates
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); /* Tightly packed texture data. */
	glGenTextures(numTextures, textureId);
	textureId[0] = SOIL_load_OGL_texture
		(
		"../Images/bricks_diffuse.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	wBitmap* bitmap = wLoadBitmap("../Images/bricks_diffuse.bmp");

	glBindTexture(GL_TEXTURE_2D, textureId[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	wFreeBitmap(bitmap);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	textureFS.SetTextureParameter(textureId[1]);

	//adding default scene objects
	//camera object should be added in the constructor and as the first object of the list for easy access
	list.push_back(new ObjectTriangle());
	list.push_back(new ObjectTriangle(-1.5, 1.75, 0.0, 0.0, 0.0, 0.0, 3.0, 3.0, 3.0, 0.75, 0.25, 0.5));
	list.push_back(new ObjectCube(-1.5, 1.5, -2.0, 0.0, 0.0, 0.0, 2.0, 2.0, 2.0, 1.0, 0.5, 0.0));
	list.push_back(new ObjectCube(1.5, -0.70, 0.0, 25.0, 30.0, 0.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0));
}

void Scene::Draw()
{
	rendererGL.ClearGLFlags();

	Matrix3D MVP, viewMatrix, modelViewMatrix, modelMatrix, translateMatrix, rotationMatrix;
	
	Matrix3D::BuildLookAtMatrix(0.0, 0.0, -12.5,	//camera position
								  0.0, 0.0, 0.0,	//point that camera looks at
								  0.0, 1.0, 0.0,	//camera up vector
								  viewMatrix);

	//create identity matrices
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, modelMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, translateMatrix);
	Matrix3D::MakeScaleMatrix(1.0, 1.0, 1.0, rotationMatrix);

	//call each object in the list draw function
	for (unsigned int i = 0; i < list.size(); i++)
	{
		float* tempSpace = list[i]->GetScale();
		Matrix3D::MakeScaleMatrix(tempSpace[0], tempSpace[1], tempSpace[2], modelMatrix);
		
		tempSpace = list[i]->GetPosition();
		Matrix3D::MakeTranslateMatrix(tempSpace[0], tempSpace[1], tempSpace[2], translateMatrix);
		
		//calculate rotation on all 3 axis
		tempSpace = list[i]->GetRotation();
		for(int r = 0; r < 3; r++)
		{
			if (tempSpace[r] != 0.0)
			{
				switch(r)
				{
				case 0:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 1.0, 0.0, 0.0, rotationMatrix);
					break;
				case 1:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 0.0, 1.0, 0.0, rotationMatrix);
					break;
				case 2:
					Matrix3D::MakeRotateMatrix(tempSpace[r], 0.0, 0.0, 1.0, rotationMatrix);
					break;
				}

				Matrix3D::MultMatrix(modelMatrix, rotationMatrix, modelMatrix);		
			}
		}
		
		Matrix3D::MultMatrix(modelMatrix, translateMatrix, modelMatrix);	//calculate world position
		Matrix3D::MultMatrix(modelViewMatrix, viewMatrix, modelMatrix);		//model - view matrix
		Matrix3D::MultMatrix(MVP, Engine::perspective, modelViewMatrix);	//model - view - projection matrix
		
		//bind CG program
		rendererGL.BindProgram(simpleVS.GetProgram());
		//rendererGL.BindProgram(simpleFS.GetProgram());
		rendererGL.BindProgram(textureFS.GetProgram());

		//Enable VS & FS profiles
		rendererGL.EnableProfile(rendererGL.GetVertexProfile());

		//Loads the fragment program into memory
		rendererGL.EnableProfile(rendererGL.GetFragmentProfile());

		//update simpleVS parameters
		simpleVS.UpdateModelViewMatrix(MVP()); 
		textureFS.SetTextureParameter(textureId[0]);

		//update shaders
		simpleVS.UpdateParameters();
		//simpleFS.UpdateParameters();
		textureFS.UpdateParameters();

		//draw geometry
		list[i]->Draw();

		//disable Vertex CGprofile
		rendererGL.DisableProfile(rendererGL.GetVertexProfile());
		rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
	}

	////disable Vertex CGprofile
	//rendererGL.DisableProfile(rendererGL.GetVertexProfile());
	//rendererGL.DisableProfile(rendererGL.GetFragmentProfile());
}

float boundBox = 5;
int xDir = 1;
int yDir = 1;
int zDir = 1;
void Scene::Update()
{
	//translate 3rd object on x-axis
	if (list[2]->GetPosition()[0] <= -boundBox) 
	{
		list[2]->SetPosition(-boundBox, list[2]->GetPosition()[1], list[2]->GetPosition()[2]);
		xDir = 1;
	}
	else if (list[2]->GetPosition()[0] >= boundBox) 
	{
		list[2]->SetPosition(boundBox, list[2]->GetPosition()[1], list[2]->GetPosition()[2]);
		xDir = -1;
	}

	//translate 3rd object on y-axis
	if (list[2]->GetPosition()[1] <= -boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], -boundBox, list[2]->GetPosition()[2]);
		yDir = 1;
	}
	else if (list[2]->GetPosition()[1] >= boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], boundBox, list[2]->GetPosition()[2]);
		yDir = -1;
	}

	//translate 3rd object on z-axis
	if (list[2]->GetPosition()[2] <= -boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], list[2]->GetPosition()[1], -boundBox);
		zDir = 1;
	}
	else if (list[2]->GetPosition()[2] >= boundBox) 
	{
		list[2]->SetPosition(list[2]->GetPosition()[0], list[2]->GetPosition()[1], boundBox);
		zDir = -1;
	}
	list[2]->TranslateOnAxis(xDir * 5.0 * Engine::deltaTime, yDir * 2.5 * Engine::deltaTime, zDir * 7.5 * Engine::deltaTime);

	//rotating 3rd & 4th object
	list[1]->RotationAroundAxis(0.0, 25 * Engine::deltaTime, 0.0); 
	list[2]->RotationAroundAxis(15 * Engine::deltaTime, 20 * Engine::deltaTime, 30 * Engine::deltaTime);
	list[3]->RotationAroundAxis(0.0, 50 * Engine::deltaTime, 0.0);
}

// return compiler error message when setting up shader programs
void Scene::checkForCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) 
	{
		printf("%s: %s: %s\n",
			"OpenGLVer2", situation, string);
		if (error == CG_COMPILER_ERROR) 
		{
			printf("%s\n", cgGetLastListing(rendererGL.GetContext()));
		}
		
		char x;
		std::cin >> x;

		exit(1);
	}
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