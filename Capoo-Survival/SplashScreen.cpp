#include "stdafx.h"
#include "SplashScreen.h"

SplashScreen::SplashScreen() :_font(AssetManager::GetFont("Font/pixel.ttf")) {
	_text.setFont(_font);
	_text.setCharacterSize(36);
	_text.setFillColor(sf::Color::White);
	_peroration.setString(L"Press any key to proceed.");
	_peroration.setFont(_font);
	_peroration.setCharacterSize(36);
	_peroration.setFillColor(sf::Color::White);
}

void SplashScreen::printText(sf::Text& text,sf::RenderWindow& window) {
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition((float)(window.getSize().x / 2), (float)(window.getSize().y / 2));
	window.draw(text);
}

void SplashScreen::show(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.display();

	const std::wstring target_text = L"Waiting...";

	const float interval = 0.2f;
	const float waitingTime = 1.0f;
	float elapsedTime = 0.0f;
	int currentPos = 0;

	sf::Event event;
	sf::Clock clock;

	bool over = false, fade_state = false;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
				if (over && event.type == sf::Event::KeyPressed)
					fade_state = true;
		}
		window.clear(sf::Color::Black);
		printText(over?_peroration:_text,window);
		window.display();
		if (fade_state) {
			const float fadeSpeed = 1.0f;
			float fadeAlpha = 0.0f;
			sf::RectangleShape fadeRect(sf::Vector2f(window.getSize().x, window.getSize().y));
			fadeRect.setFillColor(sf::Color::Black);
			while (fadeAlpha < 255.0f) {
				fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(fadeAlpha)));
				window.clear();
				printText(_peroration,window);
				window.draw(fadeRect);
				window.display();
				fadeAlpha += fadeSpeed;
			}
			break;
		}
		else if (over == false) {
			elapsedTime += static_cast<float>(clock.restart().asSeconds());
			while (elapsedTime >= interval) {
				elapsedTime -= interval;
				if (_text.getString().getSize() < target_text.size()) {
					_text.setString(target_text.substr(0, _text.getString().getSize() + 1));
				}
				else {
					elapsedTime = 0.0f;
					while (elapsedTime < waitingTime)
						elapsedTime += static_cast<float>(clock.restart().asSeconds());
					over = true;
					break;
				}
			}
		}
	}
}
