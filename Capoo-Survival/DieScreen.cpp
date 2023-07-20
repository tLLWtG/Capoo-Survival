#include "stdafx.h"
#include "DieScreen.h"
#include "AssetManager.h"
#include "Game.h"


DieScreen::DieScreen() :_font_title(AssetManager::GetFont("Font/pixel_title.ttf")) {
	_text_title.setFont(_font_title);
	_text_title.setCharacterSize(72);
	_text_title.setFillColor(sf::Color::White);
	_text_title.setString(L"GAME OVER");
	_text_title.setOrigin(_text_title.getLocalBounds().width / 2, _text_title.getLocalBounds().height / 2);
	_vibrationOffsetX = 0.0f, _vibrationOffsetY = 0.0f;
	_vibrationMagnitude = 2.0f;
	_randomEngine = std::default_random_engine(std::random_device()());
}


bool DieScreen::show(sf::RenderWindow& window) {
	_vibrationCNT = 0;
	addTextButton(sf::Vector2f((float)640, (float)550), L"MENU", "menu");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return 0;
			else if (event.type == sf::Event::MouseButtonPressed) {
				std::string buttonName = getClickButtonName(getMousePosition(window));
				if (buttonName == "menu")
					return 1;
			}
		}
		_text_title.setPosition(Game::view.getCenter().x, Game::view.getCenter().y - 100);
		if (_vibrationCNT <= 600) {
			std::uniform_real_distribution<float> dist(-_vibrationMagnitude, _vibrationMagnitude);
			_vibrationOffsetX = dist(_randomEngine);
			_vibrationOffsetY = dist(_randomEngine);
			_text_title.setPosition(_text_title.getPosition().x + _vibrationOffsetX, _text_title.getPosition().y + _vibrationOffsetY);
			_vibrationCNT++;
		}
		window.clear();
		drawButton(window);
		window.draw(_text_title);
	//	drawCrosshairs(window);
		drawMouse(window);
		window.display();
	}
		;
}

