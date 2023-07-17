#pragma once

class SplashScreen
{
public:
	SplashScreen();
	void show(sf::RenderWindow& window);

private:
	sf::Text _text;
	sf::Text _peroration;
	sf::Font& _font;

	void printText(sf::Text& text, sf::RenderWindow& window);
};