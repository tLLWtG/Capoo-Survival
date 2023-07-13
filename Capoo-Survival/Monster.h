#pragma once

#include "VisibleGameObject.h"

class Monster :
	public VisibleGameObject
{
public:
	Monster();
	~Monster();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	sf::Vector2f GetVelocity() const;

	int health;
	int maxHealth;
private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxVelocity;
};