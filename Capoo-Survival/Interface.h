#pragma once

#ifndef INTERFACE_H
#define INTERFACE_H

#include "stdafx.h"

sf::Vector2u windowSize_init = { 800,600 };

bool interface_uninitialized = true;
sf::Font font_pixel;

sf::Vector2f changeV2itoV2f(sf::Vector2i vec) {
	return sf::Vector2f((int)vec.x, (int)vec.y);
}
sf::Vector2i changeV2ftoV2i(sf::Vector2f vec) {
	return sf::Vector2i((float)vec.x, (float)vec.y);
}
sf::Vector2i getMousePosition(sf::RenderWindow& window) {
	sf::Vector2f windowPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	//	std::printf("MOUSE: %d %d\n", (int)windowPos.x, (int)windowPos.y);
	return sf::Vector2i((int)windowPos.x, (int)(windowPos.y));
}

class Button {
private:
	enum ButtonType {
		Icon, Text
	};
	ButtonType _type;
	bool _clickState = false;

	// Icon
	sf::Sprite _sprite;
	// Text
	sf::Text _text;
	sf::Sprite _icon_unpointed;
	sf::Sprite _icon_pointed;

	sf::Vector2f _position;
	sf::Rect<int> getSpriteBounds(const sf::Sprite& sprite) {
		sf::FloatRect globalBounds = sprite.getGlobalBounds();
		sf::Rect<int> rect(
			static_cast<int>(globalBounds.left),
			static_cast<int>(globalBounds.top),
			static_cast<int>(globalBounds.width),
			static_cast<int>(globalBounds.height)
		);
		return rect;
	}

	const float stressFactor = 1.2f;

public:
	std::string name;
	Button(const sf::Vector2f position, std::string const& filepath, std::string const& buttonName) {	// 中心位置，PNG文件路径，按钮命名
		_type = Icon;
		name = buttonName;

		sf::Texture& texture = AssetManager::GetTexture(filepath);
		_sprite.setTexture(texture);
		_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
		_sprite.setPosition(position.x, position.y);

		_rect = getSpriteBounds(_sprite);
	}
	Button(const sf::Vector2f position, const std::wstring& str, std::string const& buttonName) {		// 中心位置，字符串，按钮命名
		_type = Text;
		name = buttonName;

		sf::Texture& texture0 = AssetManager::GetTexture("Image/IconButton/item_0.png");
		_icon_unpointed.setTexture(texture0);
		_icon_unpointed.setOrigin(_icon_unpointed.getLocalBounds().width / 2, _icon_unpointed.getLocalBounds().height / 2);
		_icon_unpointed.setPosition(position.x, position.y);

		sf::Texture& texture1 = AssetManager::GetTexture("Image/IconButton/item_1.png");
		_icon_pointed.setTexture(texture1);
		_icon_pointed.setOrigin(_icon_pointed.getLocalBounds().width / 2, _icon_pointed.getLocalBounds().height / 2);
		_icon_pointed.setPosition(position.x, position.y);

		_text.setString(str);
		_text.setFont(font_pixel);
		_text.setCharacterSize(36);
		_text.setFillColor(sf::Color::White);
		_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
		_text.setPosition(position.x, position.y - 10);

		_rect = getSpriteBounds(_icon_unpointed);

	}

	sf::Rect<int> _rect;
	bool isPointed(sf::Vector2i clickPosition) {
		//	printf("	now is checking %s\n", this->name.c_str());
		//	printf("	Rect  top %d	left %d		height %d	width %d\n ", _rect.top, _rect.left, _rect.height, _rect.width);
		if (_type == Icon) {
			_rect = getSpriteBounds(_sprite);
		}
		else {
			_rect = getSpriteBounds(_clickState ? _icon_pointed : _icon_unpointed);
		}
		return _rect.contains(clickPosition);
	}
	const float stress_factor = 1.1;
	void updateStatus(sf::RenderWindow& window) {
		sf::Vector2i mousePos = getMousePosition(window);
		//	std::printf("MOUSE: %d %d\n", mousePos.x, mousePos.y);
		bool status = isPointed(mousePos);
		if (status != _clickState) {
			printf("button %s is pointed CHANGE  %d\n", this->name.c_str(), status);
			//	printf("Upadating %s\n", this->name.c_str());
			_clickState = status;
			if (_type == Icon) {
				_sprite.setScale(status ? stressFactor : 1.0f, status ? stressFactor : 1.0f);
			}
			else {
				_text.setFillColor(status ? (sf::Color::Black) : (sf::Color::White));
				//_text.setScale(status ? stressFactor : 1.0f, status ? stressFactor : 1.0f);
			}

		}
	}
	void draw(sf::RenderWindow& window) {
		updateStatus(window);
		if (_type == Icon)
			window.draw(_sprite);
		else {
			_clickState ? window.draw(_icon_pointed) : window.draw(_icon_unpointed);
			window.draw(_text);
		}
	}
};

class Interface {
public:
	Interface() {
		if (interface_uninitialized) {
			font_pixel.loadFromFile("Font/pixel.ttf");
			sf::Texture& texture = AssetManager::GetTexture("Image/Mouse/mouse.png");
			_mouse.setTexture(texture);
			interface_uninitialized = false;
		}
	}
	void addIconButton(const sf::Vector2f& position, std::string const& filepath, std::string const& name) {		// 中心位置，PNG文件路径，按钮名字
		_buttons.push_back(Button::Button(position, filepath, name));
	}
	void addTextButton(const sf::Vector2f& position, const std::wstring& str, std::string const& name) {
		_buttons.push_back(Button::Button(position, str, name));
	}
	void setBackground(std::string const& filepath) {
		_backgroundSprite = sf::Sprite(AssetManager::GetTexture(filepath));
	}
	void drawBackground(sf::RenderWindow& window) {
		window.draw(_backgroundSprite);
	}
	void drawButton(sf::RenderWindow& window) {
		for (Button& button : _buttons) {
			button.draw(window);
		}
	}
	void drawMouse(sf::RenderWindow& window) {
		window.setMouseCursorVisible(false);
		_mouse.setPosition(changeV2itoV2f(getMousePosition(window)));
		window.draw(_mouse);
	}
	std::string getClickButtonName(sf::Vector2i clickPosition) {
		for (Button& button : _buttons)
			if (button.isPointed(clickPosition))
				return button.name;
		return "";
	}

private:
	std::vector<Button> _buttons;
	sf::Sprite _backgroundSprite;
	sf::Sprite _mouse;
};

#endif
