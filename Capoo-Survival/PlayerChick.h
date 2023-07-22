#pragma once

#include "VisibleGameObject.h"
#include "Animator.h"
#include "JumpText.h"
#include "Skill_Spurt.h"

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
	float lastHeal;
	Animator animator;
	void playerDie();
	void boundCheck();
	void upgrade();

	JumpText _jumptext;
	Skill* _skill;
	
};