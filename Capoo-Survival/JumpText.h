#pragma once

#ifndef JUMPTEXT_H
#define JUMPTEXT_H

#include "VisibleGameObject.h"

class JumpText {
public:
	JumpText(VisibleGameObject* master);	// ���������
	void SetDamage(int damage);
	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& window);
	

private:
	void SetAlpha(float alpha);

	sf::Font& _font;
	sf::Text _damegeText;
	const float dieoutTime = 0.35f;
	float remainder;

	VisibleGameObject* _master;	// ���������
};

#endif
