#pragma once

#include "stdafx.h"
#include "Interface.h"

class Mainmenu : public Interface {
public:
	Mainmenu() : Interface() {

	}
	void init() {
		if (uninitialized) {
		//	setBackground("Image/Mainmenu/background_.png");
			addIconButton(sf::Vector2f(730, 400), "Image/IconButton/setting.png", "setting");
			addIconButton(sf::Vector2f(723, 480), "Image/IconButton/music.png", "music");
			addIconButton(sf::Vector2f(728, 555), "Image/IconButton/volume.png", "volume");
			addTextButton(sf::Vector2f(400, 200), L"START", "START");
			addTextButton(sf::Vector2f(400, 300), L"CONTINUE", "CONTINUE");
			addTextButton(sf::Vector2f(400, 400), L"ACHIEVEMENT", "ACHIEVEMENT");
			uninitialized = false;
		}
	}
	void show(sf::RenderWindow& window) {
	//	drawBackground(window);
		drawButton(window);
		drawMouse(window);
	}
	void click(sf::RenderWindow& window) {
		sf::Vector2i clickPosition = getMousePosition(window);
		std::string clickbottonName = getClickButtonName(clickPosition);
		printf("BUTTON %s is clicked\n", clickbottonName.c_str());
	}
private:
	bool uninitialized = true;
};