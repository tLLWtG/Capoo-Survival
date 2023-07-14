#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Interface.h"
#include "Game.h"
#include "Animation.h"

class Mainmenu : public Interface {
public:

	Mainmenu() : Interface() {

	}
	void init() {
		if (uninitialized) {
			setBackground("Image/Mainmenu/background_glass.png");
			addIconButton(sf::Vector2f(1210, 520), "Image/IconButton/setting.png", "setting");
			addIconButton(sf::Vector2f(1203, 600), "Image/IconButton/music.png", "music");
			addIconButton(sf::Vector2f(1208, 675), "Image/IconButton/volume.png", "volume");
			addTextButton(sf::Vector2f(640, 260), L"START", "START");
			addTextButton(sf::Vector2f(640, 360), L"CONTINUE", "CONTINUE");
			addTextButton(sf::Vector2f(640, 460), L"ACHIEVEMENT", "ACHIEVEMENT");
			uninitialized = false;
		}
	}
	Game::GameState show(sf::RenderWindow& window) {
		static sf::Sprite background_sprite;
		background_sprite.setPosition(0,300);
		Animator animator(background_sprite);
		auto& cloudAnimation = animator.CreateAnimation("clouds", "Image/Mainmenu/cloud_1285x61.png", sf::seconds(2), true);
		cloudAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(1285, 61), 30);
		sf::Clock clock;

		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) 
					return Game::GameState::Exiting;
				else if (event.type == sf::Event::MouseButtonPressed) {
					std::string buttonName = getClickButtonName(getMousePosition(window));
					if (buttonName == "START")
						return Game::GameState::Playing;
					///////////////////////////////////
				}
			}
			animator.Update(clock.restart());
			window.clear();
			drawBackground(window);
			window.draw(background_sprite);
			drawButton(window);
			drawMouse(window);
			window.display();
		}
	}
	void click(sf::RenderWindow& window) {
		sf::Vector2i clickPosition = getMousePosition(window);
		std::string clickbottonName = getClickButtonName(clickPosition);
		printf("BUTTON %s is clicked\n", clickbottonName.c_str());
	}
private:
	bool uninitialized = true;
};

#endif
