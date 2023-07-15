#pragma once

#include "VisibleGameObject.h"
#include "Animator.h"

class Weapon :public VisibleGameObject {
protected:
	Animator m_Animator;
	int attackPower;
	float attackTime;
	float attackDuration;
	// 暂时还没写除了攻击外的别的属性

public:
	enum WeaponState {
		Attacking, Holding
	};
	WeaponState weaponstate;

	Weapon() : weaponstate(Holding),m_Animator(GetSprite()) {

	}
	virtual void Update(float elapsedTime) {
		if (weaponstate == Attacking) {
			attackTime += elapsedTime;
			if (attackTime >= attackDuration) 
				Hold();
		}
		m_Animator.Update(sf::seconds(elapsedTime));
	}
	virtual void Draw(sf::RenderWindow& window) {
		window.draw(GetSprite());
	}
	virtual void Fire() {
		if (weaponstate == Holding) {
			weaponstate = Attacking;
			attackTime = 0.0f;
			m_Animator.SwitchAnimation("Attack");
		}
	}
	virtual void Hold() {
		if (weaponstate == Attacking) {
			weaponstate = Holding;
			m_Animator.SwitchAnimation("Hold");
		}
	}/*
	bool isHit()	// 碰撞检测可能需要怪物的接口
	// //////////////
	*/
};
