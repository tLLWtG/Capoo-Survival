#pragma once

#include "Obstacle.h"
#include "VisibleGameObject.h"


class ObstacleManager
{
public:

	ObstacleManager();
	~ObstacleManager();

	std::set<std::string>& GetObstacleSet();
private:
	static char cnt;
	std::set<std::string>ObstacleSet;
};