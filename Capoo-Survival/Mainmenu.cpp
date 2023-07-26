#include "stdafx.h"
#include "Game.h"
#include "Mainmenu.h"
#include "SettingScreen.h"
#include "Archive.h"
#include "PlayerChick.h"

Mainmenu::Mainmenu() : Interface() {

}

Mainmenu::MenuResult Mainmenu::show(sf::RenderWindow& window) {
	setBackground("Image/Mainmenu/background_glass.png");
	addIconButton(sf::Vector2f(1203, 520), "Image/IconButton/setting.png", "setting");
	addIconButton(sf::Vector2f(1203, 600), "Image/IconButton/music.png", "music");
	addIconButton(sf::Vector2f(1208, 675), "Image/IconButton/volume.png", "volume");
	
	Archive::load();
	printf("Game::time =%f\n", Game::addTime);
	if (!Archive::load().empty()) {
		addTextButton(sf::Vector2f(640, 260), L"NEW", "NEW");
		addTextButton(sf::Vector2f(640, 360), L"CONTINUE", "CONTINUE");
		addTextButton(sf::Vector2f(640, 460), L"HELP", "HELP");
		addTextButton(sf::Vector2f(640, 560), L"QUIT", "QUIT");
	}
	else {
		addTextButton(sf::Vector2f(640, 260), L"NEW", "NEW");
		addTextButton(sf::Vector2f(640, 360), L"HELP", "HELP");
		addTextButton(sf::Vector2f(640, 460), L"QUIT", "QUIT");
	}
	

	static sf::Sprite background_sprite;
	background_sprite.setPosition(0 + getWindowStart().x, 300.0f + getWindowStart().y);
	Animator animator(background_sprite);
	auto& cloudAnimation = animator.CreateAnimation("clouds", "Image/Mainmenu/cloud_1285x61.png", sf::seconds(2), true);
	cloudAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(1285, 61), 30);
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return Mainmenu::MenuResult::Exiting;
			else if (event.type == sf::Event::MouseButtonPressed) {
				std::string buttonName = getClickButtonName(getMousePosition(window));
				if (buttonName == "NEW") {
					Game::addTime = 0.0f;
					Game::GetGameObjectManager().Remove("player");
					PlayerChick* player = new PlayerChick();
					player->SetPosition(0, 0);
					Game::GetGameObjectManager().Add("player", player);
					return Mainmenu::MenuResult::Playing;
				}
				else if (buttonName == "CONTINUE") {
					Game::LoadArchive();
					return Mainmenu::MenuResult::Playing;
				}
				else if (buttonName == "QUIT") {
					return Mainmenu::MenuResult::Exiting;
				}
				else if (buttonName == "setting")
					return Mainmenu::MenuResult::Setting;
				else if (buttonName == "music") {
					for (Button& button : _buttons)
						if (button.name == "music") {
							button.state ^= 1;
							if (button.state)
								SettingScreen::setMusic(0.0f);
							else
								SettingScreen::setMusic(100.0f);
						}

				}
				else if (buttonName == "volume") {
					for (Button& button : _buttons)
						if (button.name == "volume") {
							button.state ^= 1;
							if (button.state)
								SettingScreen::setVolume(0.0f);
							else
								SettingScreen::setVolume(100.0f);
						}
				}
				else if (buttonName == "HELP") {
					for (Button& button : _buttons)
						if (button.name == "HELP") {
							if (Game::_helpscreen.show(window) == 0)
								return Mainmenu::MenuResult::Exiting;
						}
				}
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

void Mainmenu::click(sf::RenderWindow& window) {
	sf::Vector2i clickPosition = getMousePosition(window);
	std::string clickbottonName = getClickButtonName(clickPosition);
	printf("BUTTON %s is clicked\n", clickbottonName.c_str());
}
