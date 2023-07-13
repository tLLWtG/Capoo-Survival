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

	float health;
	float maxHealth;
	float baseDamage;
	sf::Vector2i direction;
	int score;
	void getDamage(float damage);

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxVelocity;
};