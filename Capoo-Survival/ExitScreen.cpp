#include "stdafx.h"
#include "ExitScreen.h"
#include "Game.h"
#include "Archive.h"
#include "PlayerChick.h"

ExitScreen::ExitScreen():_font_exit(AssetManager::GetFont("Font/Fixedsys62.ttf")) {
}

int ExitScreen::show(sf::RenderWindow& window) {
	addTextButton(sf::Vector2f(640, 260), L"SAVE", "save");
	addTextButton(sf::Vector2f(640, 360), L"NOT SAVE", "notsave");

	sf::Text text;
	text.setFont(_font_exit);
	text.setCharacterSize(70);

	bool flag = true;
	float remainder;
	const float maxTime = 2.0f;
	sf::Event event;
	sf::Clock clock;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return 0;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				return 1;
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::string buttonName = getClickButtonName(getMousePosition(window));
				if (buttonName != "")
					Button::_sound.play();
				if (buttonName == "save") {
					if (Archive::save())
						text.setString("SAVE SUCCEEDED!");
					else 
						text.setString("SAVE FAILED!");
					text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
					text.setPosition(Game::view.getCenter());
					flag = false;
					remainder = maxTime;
					clock.restart();
					break;
				}
				else if (buttonName == "notsave") {
					Game::addTime = 0.0f;
					Game::GetGameObjectManager().Remove("player");
					PlayerChick* player = new PlayerChick();
					player->SetPosition(0, 0);
					Game::GetGameObjectManager().Add("player", player);
					return 2;
				}
			}
		}
		window.clear();
		window.clear(sf::Color(52, 103, 49));
		Game::GetGameObjectManager().DrawAll(window);
		darkenWindow(window);
		if (flag)
			drawButton(window);
		else {
			if (remainder > 0.0f) {
				text.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, remainder / maxTime * 255.0f));
				remainder -= clock.restart().asSeconds();
				window.draw(text);
			}
			else
				return 3;
		}
		drawMouse(window);
		window.display();
	}
	return 1;
}