#pragma once
#pragma once
#include "VisibleGameObject.h"

class Obstacle : public VisibleGameObject
{
public:
	Obstacle();
	~Obstacle();
	void Update(float);

private:
	int _numOfObstacles;
};