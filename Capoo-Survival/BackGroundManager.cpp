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
	for (cnt = 0; cnt < 50; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);

	}
	filename = "Image/BackGround/test2.png";
	
	for (; cnt <= 100; cnt++)
	{
		std::string name = "BackGround" + std::to_string(++cnt);
		VisibleGameObject* background = new BackGround(filename);

		Game::GetGameObjectManager().Add(name, background);
	}
}

BackGroundManager::~BackGroundManager()
{

}
