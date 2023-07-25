#pragma once

#ifndef SettingScreen_H
#define SettingScreen_H

class Slider {
public:
	bool state = false;
	int _max_value, _current_value;
	Slider(float width, float height, float max_value, float current_value) :_width(width), _height(height),
		_max_value(max_value), _current_value(current_value) {
		_background.setSize(sf::Vector2f(width + 2 * _thickness, height + 2 * _thickness));
		_background.setOrigin(_background.getLocalBounds().width / 2, _background.getLocalBounds().height / 2);
		_background.setOutlineColor(sf::Color::Black);
		_background.setOutlineThickness(_thickness);
		_background.setFillColor(sf::Color(100, 100, 100, 150));

		_current_slider.setSize(sf::Vector2f(width * current_value / max_value, height));
		_current_slider.setFillColor(sf::Color::Blue);
	}
	void setPosition(int x, int y) {
		_background.setPosition(x, y);
		_current_slider.setPosition(x - _background.getLocalBounds().width / 2 + 2 * _thickness, y - _background.getLocalBounds().height / 2 + 2 * _thickness);
	}
	void follow(sf::RenderWindow& window) {
		sf::Vector2i mousePosition = getMousePosition(window);
		if (0.0 <= mousePosition.x - _current_slider.getPosition().x && mousePosition.x - _current_slider.getPosition().x <= _width)
			_current_slider.setSize(sf::Vector2f(mousePosition.x - _current_slider.getPosition().x, _height));
	}
	float getValue() {
		return _current_slider.getSize().x / _width * _max_value;
	}
	void draw(sf::RenderWindow& window) {
		window.draw(_background);
		window.draw(_current_slider);
	}
	sf::FloatRect getGlobalBounds() {
		return _background.getGlobalBounds();
	}
private:
	int _width, _height;
	sf::RectangleShape _current_slider;
	sf::RectangleShape _background;
	const float _thickness = 3.0f;
};

class SettingScreen :public Interface {
public:

	SettingScreen();
	int show(sf::RenderWindow& window, int _from);	// op：开启设置的背景


private:
	sf::Event _event;

	sf::Texture& _title_texture;
	sf::Sprite _text_title;
	sf::Sprite _frame_sprite;

	float current_volume;
	sf::Sprite _music_icon;
	Slider _music;	// 音乐音量

	sf::Sprite _volume_icon;
	Slider _volume;	// 音效音量（

	void draw_title(sf::RenderWindow& window);
	void draw_frame(sf::RenderWindow& window);

	void detectPressMouse(sf::RenderWindow& window);

};

#endif
