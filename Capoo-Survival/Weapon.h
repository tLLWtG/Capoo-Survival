#pragma once

#include "VisibleGameObject.h"
#include "Animator.h"
#include "Monster.h"

class Weapon :public VisibleGameObject {

protected:
	Animator m_Animator;
	Animator m_special;
	sf::Sprite _special_sprite;

	int attackPower;
	float attackTime;
	float attackDuration;
	// 暂时还没写除了攻击外的别的属性

	int startAngle;

public:
	static sf::Music _sound;

	enum WeaponState {
		Attacking, Holding
	};
	WeaponState weaponstate;

	Weapon();

	virtual void setHandle();
	virtual void resetHandle();
	virtual void Update(float elapsedTime);
	virtual void Draw(sf::RenderWindow& window);
	virtual void ChangeDirection(sf::Vector2i direction);
	virtual void Fire();
	virtual void Hold();
	void SetPosition(float x, float y);
	void setSize(float multiple);
	bool isHit(const Monster* moster);

};
