#include "SceneManager.h"

SceneManager::SceneManager()
{
	sceneList[SCENE_MAINMENU] = new SceneMenu;
	sceneList[SCENE_FOOTBALL] = new SceneCollision;
	scene = nullptr;
	swap = false;
}


void SceneManager::Init(Scene** s)
{
	scene = s;
}


void SceneManager::ChangeScene(SCENE_TYPE scenetype)
{
	swap = true;
	currentScene = scenetype;
}

void SceneManager::Update()
{
	if (swap == true)
	{
		if (*scene)
		{
			(*scene)->Exit();
			delete* scene;
			*scene = nullptr;
		}
		*scene = sceneList[currentScene]->Clone();
		(*scene)->Init();
		(*scene)->Update(0);
		swap = false;
	}
}

SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager;
	}
	return instance;
}

SceneManager::~SceneManager()
{
	for (auto s : sceneList)
	{
		delete s;
	}
}