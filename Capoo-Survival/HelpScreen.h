#pragma once

#ifndef HELPSCREEN_H
#define HELPSCREEN_H

#include "AssetManager.h"

class HelpScreen :public Interface {
public:

	HelpScreen();
	bool show(sf::RenderWindow& window);


private:
	sf::Texture& _title_texture;
	sf::Sprite _text_title;
	sf::Sprite _frame_sprite;
	sf::Font _help_font;

	void draw_title(sf::RenderWindow& window);
	void draw_frame(sf::RenderWindow& window);

	std::vector<sf::Text> _paragraph;

};


#endif 