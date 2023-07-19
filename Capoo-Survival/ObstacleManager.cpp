#include "stdafx.h"
#include "ObstacleManager.h"
#include "GameObjectManager.h"
#include "Game.h"

ObstacleManager::ObstacleManager()
{

	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;
	std::string filename = "Image/Obstacle/test1.png";
	std::string name = "Obstacle1";
	int i;
	for (i = 0; i <= 9; i++)
	{
		filename.erase(filename.begin() + 19);
		filename.insert(filename.begin() + 19, '0' + i);
		name.pop_back();
		name.push_back(i + '0');

		Obstacle* obstacle = new Obstacle(filename);

		Game::GetGameObjectManager().Add(name, obstacle);
		ObstacleSet.insert(name);
		
	}
	filename = "Image/Obstacle/test10.png";
	name = "Obstacle10";
	for (i = 0; i <= 9; i++)
	{
		filename.erase(filename.begin() + 20);
		filename.insert(filename.begin() + 20, '0' + i);
		name.pop_back();
		name.push_back(i + '0');

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