#pragma once

#include "VisibleGameObject.h"

class PlayerChick :
	public VisibleGameObject
{
public:
	PlayerChick();
	~PlayerChick();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	sf::Vector2f GetVelocity() const;

	int health;
	int maxHealth;
	int score;

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxVelocity;
};