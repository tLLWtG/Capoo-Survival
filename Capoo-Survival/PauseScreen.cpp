#include "stdafx.h"
#include "Interface.h"
#include "PauseScreen.h"
#include "AssetManager.h"
#include "Game.h"

PauseScreen::PauseScreen() :_font_title(AssetManager::GetFont("Font/pixel_title.ttf")) {
	_text_title.setFont(_font_title);
	_text_title.setCharacterSize(72);
	_text_title.setFillColor(sf::Color::White);
	_text_title.setString(L"PAUSE");
	_text_title.setOrigin(_text_title.getLocalBounds().width / 2, _text_title.getLocalBounds().height / 2);

	sf::Texture& texture = AssetManager::GetTexture("Image/Mainmenu/PauseMenu.png");
	_frame_sprite.setTexture(texture);
	_frame_sprite.setOrigin(_frame_sprite.getLocalBounds().width / 2, _frame_sprite.getLocalBounds().height / 2);
	_frame_sprite.setPosition(Game::view.getCenter());

}

int PauseScreen::show(sf::RenderWindow& window) {
	_text_title.setPosition(getWindowStart().x + 640, getWindowStart().y + 100);
	addTextButton(sf::Vector2f(640, 250), L"RESUME", "resume");
	addTextButton(sf::Vector2f(640, 350), L"SETTING", "setting");
	addTextButton(sf::Vector2f(640, 450), L"QUIT", "quit");

	_frame_sprite.setPosition(Game::view.getCenter());

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return 0;
			else if (event.type == sf::Event::MouseButtonPressed) {
				std::string buttonName = getClickButtonName(getMousePosition(window));
				if (buttonName == "resume") {
					while (window.pollEvent(event) && event.type == sf::Event::MouseButtonPressed);
					sf::sleep(sf::milliseconds(200));	// È¥¶¶¶¯
					return 1;
				}
				else if (buttonName == "quit")
					return 2;
			}
		}
		window.clear(sf::Color(52, 103, 49));
		Game::GetGameObjectManager().DrawAll(window);
		darkenWindow(window);
		window.draw(_frame_sprite);
		drawButton(window);
		drawMouse(window);
		window.display();
	}

}