#include "stdafx.h"
#include "BackGroundManager.h"
#include "GameObjectManager.h"
#include "Game.h"

int BackGroundManager::cnt = 1;
BackGroundManager::BackGroundManager()
{
	
	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;
	std::string filename = "Image/BackGround/test0.png";
	std::string name = "BackGround1";
	int i;
	for (i = 0; i <= 9; i++)
	{
		filename.erase(filename.begin() + 21);
		filename.insert(filename.begin() + 21, '0' + i);
		name.pop_back();
		name.push_back(i + '0');

		VisibleGameObject* BackGround = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, BackGround);

	}
	filename = "Image/BackGround/test10.png";
	name = "BackGround10";
	for (i = 0; i <= 9; i++)
	{
		filename.erase(filename.begin() + 22);
		filename.insert(filename.begin() + 22, '0' + i);
		name.pop_back();
		name.push_back(i + '0');

		VisibleGameObject* BackGround = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, BackGround);
	}
}

BackGroundManager::~BackGroundManager()
{

}

void BackGroundManager::Update()
{

	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;

	std::string filename = "Image/BackGround/test19.png";
	std::string name = "BackGround" + std::to_string(++cnt);

	VisibleGameObject* background = new BackGround(filename);
	Game::GetGameObjectManager().Add(name,background);
}