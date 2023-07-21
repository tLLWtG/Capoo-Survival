#include "stdafx.h"
#include "ObstacleManager.h"
#include "GameObjectManager.h"
#include "Game.h"

ObstacleManager::ObstacleManager()
{

	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;
	std::string filename = "Image/Obstacle/test1.png";
	int i;
	for (i = 0; i <= 9; i++)
	{
		std::string name = "BackGround" + std::to_string(++i);
		Obstacle* obstacle = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, obstacle);
		ObstacleSet.insert(name);
		
	}

	filename = "Image/Obstacle/test2.png";
	for (; i <= 19; i++)
	{
		std::string name = "BackGround" + std::to_string(++i);
		Obstacle* obstacle = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, obstacle);
		ObstacleSet.insert(name);

	}
	filename = "Image/Obstacle/test3.png";
	for (; i <= 29; i++)
	{
		std::string name = "BackGround" + std::to_string(++i);
		Obstacle* obstacle = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, obstacle);
		ObstacleSet.insert(name);

	}
}

ObstacleManager::~ObstacleManager()
{

}


std::set<std::string>& ObstacleManager::GetObstacleSet()
{
	return ObstacleSet;
}

int ObstacleManager::cnt = 6;

int ObstacleManager::GetNumofObstacle()
{
	return cnt;
}