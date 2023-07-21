#pragma once

#ifndef DIESCREEN_H
#define DIESCREEN_H

#include "Interface.h"
#include "Animator.h"

class DieScreen : public Interface {
public:

	DieScreen();
	bool show(sf::RenderWindow& window);


private:
	sf::Text _text_title;
	sf::Font& _font_title;

	float _vibrationOffsetX;
	float _vibrationOffsetY;
	float _vibrationMagnitude;
	int _vibrationCNT = 0;
	std::default_random_engine _randomEngine;
};


#endif