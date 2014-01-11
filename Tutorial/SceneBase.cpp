#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
{
}


SceneBase::~SceneBase()
{
	BaseObject* scene;
	for (int i = 0; i < list.size(); i++)
	{
		scene = list[i];
		delete(scene);
	}

	list.clear();
}