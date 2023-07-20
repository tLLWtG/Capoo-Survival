#pragma once
#include "VisibleGameObject.h"

class BackGround : public VisibleGameObject
{
public:
	BackGround(std::string filename);
	~BackGround();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

};