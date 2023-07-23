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

	float cdTime;	// �����ȴʱ��
	float remainingWaitingTime;	// ʣ����ȴʱ��

	float attackTime;	// ���������Ѿ�����ʱ��
	float attackDuration;	// ����������󲥷�ʱ��

	enum SkillState {
		Attacking, Waiting
	};
	SkillState skillstate;

};

#endif
