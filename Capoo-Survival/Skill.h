#pragma once
#ifndef SKILL_H
#define SKILL_H

#include "Monster.h"

class Skill :public VisibleGameObject {
public:
	Skill();
	virtual void Update(float elapsedTime);
	virtual void Draw(sf::RenderWindow& window);
	virtual void ChangeDirection(sf::Vector2i direction);
	virtual void Fire();
	virtual void Wait();
	bool isHit(const Monster* moster);

protected:
	Animator m_Animator;
	int startAngle;

	float cdTime;	// 最大冷却时间
	float remainingWaitingTime;	// 剩余冷却时间

	float attackTime;	// 攻击动画已经播放时间
	float attackDuration;	// 攻击动画最大播放时间

	enum SkillState {
		Attacking, Waiting
	};
	SkillState skillstate;

};

#endif
