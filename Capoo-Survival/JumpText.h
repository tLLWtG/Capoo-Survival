#pragma once

#ifndef JUMPTEXT_H
#define JUMPTEXT_H

#include "VisibleGameObject.h"
#include "Animator.h"

class JumpText {
public:
	JumpText(VisibleGameObject* master);	// 跟随的物体
	void SetDamage(int damage);
	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	

private:
	bool isDamage;

	void SetAlpha(float alpha);
	bool belongtoPlayer();

	sf::Font& _font;
	sf::Text _damegeText;
	const float dieoutTime = 1.0f;
	const float waitingTime = 0.3f;
	float remainder;
	sf::Sprite _healing;
	Animator m_healingAnimator;

	VisibleGameObject* _master;	// 跟随的主体
};

#endif
