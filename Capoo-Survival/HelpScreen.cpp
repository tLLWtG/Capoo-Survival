#include "stdafx.h"
#include "Interface.h"
#include "HelpScreen.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Game.h"


HelpScreen::HelpScreen():_title_texture(AssetManager::GetTexture("Image/Screen/help_title.png")), _font(AssetManager::GetFont("Font/Fixedsys62.ttf")) {
	_text_title.setTexture(_title_texture);
	_text_title.setScale(1.0f, 1.2f);
	_text_title.setOrigin(_text_title.getLocalBounds().width / 2, _text_title.getLocalBounds().height / 2);

	sf::Texture& texture = AssetManager::GetTexture("Image/Mainmenu/Frame.png");
	_frame_sprite.setTexture(texture);
	_frame_sprite.setOrigin(_frame_sprite.getLocalBounds().width / 2, _frame_sprite.getLocalBounds().height / 2);
	_frame_sprite.setScale(1.24f, 1.24f);
}

bool HelpScreen::show(sf::RenderWindow& window) {
	static sf::Sprite background_sprite;
	background_sprite.setPosition(0 + getWindowStart().x, 300.0f + getWindowStart().y);
	Animator animator(background_sprite);
	auto& cloudAnimation = animator.CreateAnimation("clouds", "Image/Mainmenu/cloud_1285x61.png", sf::seconds(2), true);
	cloudAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(1285, 61), 30);

	setBackground("Image/Mainmenu/background_glass.png");
	
	sf::Clock clock;
	sf::Event _event;
	while (window.isOpen()) {
		while (window.pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				return 0;
			if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
				return 1;

		}
		window.clear();
		animator.Update(clock.restart());
		drawBackground(window);
		window.draw(background_sprite);
		
		draw_title(window);
		draw_frame(window);
		
		drawMouse(window);

		window.display();
	}

	
}


void HelpScreen::draw_title(sf::RenderWindow& window) {
	_text_title.setPosition(Game::view.getCenter().x, Game::view.getCenter().y - 250);
	window.draw(_text_title);
}
void HelpScreen::draw_frame(sf::RenderWindow& window) {
	_frame_sprite.setPosition(Game::view.getCenter().x, Game::view.getCenter().y + 75);
	window.draw(_frame_sprite);
}