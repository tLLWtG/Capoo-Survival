#include "stdafx.h"
#include "BackGroundManager.h"
#include "GameObjectManager.h"
#include "BackGround.h"
#include "Game.h"


BackGroundManager::BackGroundManager()
{
	
	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;
	
	std::string filename = "Image/BackGround/test1.png";
	int cnt = 0;
	for (cnt = 0; cnt < 10; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
	filename = "Image/BackGround/test2.png";
	
	for (; cnt <= 20; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
	filename = "Image/BackGround/test3.png";

	for (; cnt <= 30; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
	filename = "Image/BackGround/test4.png";

	for (; cnt <= 40; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
	filename = "Image/BackGround/test5.png";

	for (; cnt <= 50; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
	filename = "Image/BackGround/test6.png";

	for (; cnt <= 60; cnt++)
	{
		std::string name = "ABackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
		BackGroundSet.insert(name);
	}
}

BackGroundManager::~BackGroundManager()
{

}
std::set<std::string>& BackGroundManager::GetBackGroundSet()
{
	return BackGroundSet;
}
