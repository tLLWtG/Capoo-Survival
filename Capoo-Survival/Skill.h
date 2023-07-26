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

	static float cdTime;	// �����ȴʱ��
	static float remainingWaitingTime;	// ʣ����ȴʱ��

	static sf::Music _sound;

protected:
	Animator m_Animator;
	int startAngle;

	float attackPower;

	float attackTime;	// ���������Ѿ�����ʱ��
	float attackDuration;	// ����������󲥷�ʱ��

	enum SkillState {
		Attacking, Waiting
	};
	SkillState skillstate;

};

#endif
