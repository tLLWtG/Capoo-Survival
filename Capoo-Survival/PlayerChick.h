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
	float scores;
	void getDamage(float damage);
	void getScore(float score);

private:
	sf::Vector2f _velocity;
	float _maxVelocity;
	
	void playerDie();
	void boundCheck();
	void upgrade();
};