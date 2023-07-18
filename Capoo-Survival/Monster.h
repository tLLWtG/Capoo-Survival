#pragma once

#include "VisibleGameObject.h"
#include "Animator.h"
class Monster :
	public VisibleGameObject
{
public:
	Monster(std::string filename, std::string name);
	~Monster();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	sf::Vector2f GetVelocity() const;

	float health;
	float maxHealth;
	float baseDamage;
	float scores;
	void getDamage(float damage);

private:
	void monsterDie();
	void upgrade();
	void chase();
	void attack();

	float lastAttackTime;
	sf::Vector2f _velocity;
	float _maxVelocity;
	Animator animator;
};