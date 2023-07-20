#pragma once

#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

class PauseScreen : public Interface {
public:
	PauseScreen();
	int show(sf::RenderWindow& window);


private:
	sf::Font& _font_title;
	sf::Text _text_title;
	sf::Sprite _frame_sprite;
};




#endif