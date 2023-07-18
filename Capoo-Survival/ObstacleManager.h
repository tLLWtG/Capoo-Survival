#pragma once

#include "Obstacle.h"
#include "VisibleGameObject.h"


class ObstacleManager
{
public:

	ObstacleManager();
	~ObstacleManager();

	int GetNumofObstacle();
	std::set<std::string>& GetObstacleSet();
private:
	static int cnt;
	std::set<std::string>ObstacleSet;
};