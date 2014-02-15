#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
{
}


SceneBase::~SceneBase()
{
	//Delete all objects in list
	for (unsigned int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}

	list.clear();
}