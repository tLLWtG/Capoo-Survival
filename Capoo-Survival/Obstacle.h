#pragma once
#include "VisibleGameObject.h"

class Obstacle : public VisibleGameObject
{
public:
	Obstacle(std::string filename);
	~Obstacle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	sf::Rect<float> GetBoundingRect() const;

private:

};