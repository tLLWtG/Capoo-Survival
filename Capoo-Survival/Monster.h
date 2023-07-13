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

	float health;
	float maxHealth;
	float baseDamage;
	int score;
	void getDamage(float damage);

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxVelocity;
};