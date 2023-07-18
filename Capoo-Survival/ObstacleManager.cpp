#include "stdafx.h"
#include "ObstacleManager.h"
#include "GameObjectManager.h"
#include "Game.h"
char ObstacleManager::cnt = '1';


ObstacleManager::ObstacleManager()
{

	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;

	std::string filename = "Image/Obstacle/test1.png";
	std::string name = "Obstacle1";

	Obstacle* obstacle = new Obstacle(filename);

	Game::GetGameObjectManager().Add(name, obstacle);
	ObstacleSet.insert(name);
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