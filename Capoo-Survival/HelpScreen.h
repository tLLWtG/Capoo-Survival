#pragma once

#ifndef HELPSCREEN_H
#define HELPSCREEN_H

class Paragraph {	// ¶ÎÂä
public:
	Paragraph(const std::wstring str, const float width, const sf::Vector2f position) :_str(str), _width(width), _position(position) {
		sf::Text text;
		reset();
	}
	void setCharacterSize(float x) {
		_CharacterSize = x;
		reset();
	}
	void draw(sf::RenderWindow& window) {
		if (line.front().getCharacterSize() != _CharacterSize) {
			reset();
		}
		for (int i = 0; i < line.size(); i++)
			window.draw(line[i]);
	}
	void reset() {
		sf::Vector2f start(_position.x - _width / 2, _position.y);
		size_t last = 0, i = 0;
		sf::Text temp;
		for (i = 0; i < _str.size(); i++) {
			temp.setString(_str.substr(last, i));
			if (temp.getLocalBounds().width > _width) {
				temp.setString(_str.substr(last, i - 1));
				temp.setPosition(start);
				line.push_back(temp);
				last = i + 1;
				start = sf::Vector2f(start.x, start.y + temp.getGlobalBounds().top + temp.getGlobalBounds().height + _lineSpace);
			}
		}
		if (i - 1 >= last) {
			temp.setString(_str.substr(last, i - 1));
			temp.setPosition(start);
			line.push_back(temp);
		}
	}

private:
	std::wstring _str;
	std::vector<sf::Text> line;
	
	float _width;	// ÏÞÖÆÐÐ¿í
	float _lineSpace = 2.0f;
	sf::Vector2f _position;

	float _CharacterSize;
};

class HelpScreen :public Interface {
public:

	HelpScreen();
	bool show(sf::RenderWindow& window);


private:
	sf::Texture& _title_texture;
	sf::Sprite _text_title;
	sf::Sprite _frame_sprite;

	void draw_title(sf::RenderWindow& window);
	void draw_frame(sf::RenderWindow& window);

	sf::Font& _font;
};


#endif 