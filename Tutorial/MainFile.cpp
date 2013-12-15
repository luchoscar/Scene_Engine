// Tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine* pEngine = new Engine();
	
	pEngine->Init(argc, argv);
	pEngine->Run();

	delete pEngine;

	return 0;
}
