#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Game.h"

class Obstacle : public VisibleGameObject
{
public:
	Obstacle();
	~Obstacle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:
	static char cnt;
};