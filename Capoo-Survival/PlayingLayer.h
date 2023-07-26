#pragma once

#ifndef PLAYINGLAYER_H
#define PLAYINGLAYER_H

#include "stdafx.h"
#include "Interface.h"

class PlayingLayer : public Interface {
public:
	PlayingLayer();
	void showHP(sf::RenderWindow& window);
	void showCD(sf::RenderWindow& window);

private:
	sf::Text _hp_text;
	sf::Text _hp_value;

	sf::Text _cd_text;
	sf::Text _cd_value;
};


#endif
