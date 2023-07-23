#pragma once

#include "VisibleGameObject.h"
#include "Animator.h"
#include "JumpText.h"

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
	void monsterDie();

private:
	//void upgrade();
	void chase();
	void attack();

	std::string _name;
	float lastAttackTime;
	sf::Vector2f _velocity;
	float _maxVelocity;
	float deadTime;
	Animator animator;

	JumpText _jumptext;
};