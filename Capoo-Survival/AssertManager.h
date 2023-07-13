#pragma once

#include "Stdafx.h"

class AssertManager
{
public:
	AssertManager();
	~AssertManager();

	sf::Font GetFont(std::string filename);
	sf::Music GetMusic(std::string filename);

private:
	map<std::string, sf::Font*> _fontObjects;
	map<std::string, sf::Music*> _musicObjects;
};