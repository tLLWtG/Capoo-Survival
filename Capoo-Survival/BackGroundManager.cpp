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
	for (cnt = 0; cnt < 30; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);

	}
	filename = "Image/BackGround/test2.png";
	
	for (; cnt <= 60; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
	filename = "Image/BackGround/test3.png";

	for (; cnt <= 90; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
	filename = "Image/BackGround/test4.png";

	for (; cnt <= 120; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
	filename = "Image/BackGround/test5.png";

	for (; cnt <= 150; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
	filename = "Image/BackGround/test6.png";

	for (; cnt <= 180; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
}

BackGroundManager::~BackGroundManager()
{

}
