#include "stdafx.h"
#include "Interface.h"
#include "AssetManager.h"
#include "Game.h"


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
sf::Vector2f getWindowStart() {
	return sf::Vector2f(Game::view.getCenter().x - Game::GetWindow().getSize().x / 2.0f, Game::view.getCenter().y - Game::GetWindow().getSize().y / 2.0f);
}

sf::Rect<int> Button::getSpriteBounds(const sf::Sprite& sprite) {
	sf::FloatRect globalBounds = sprite.getGlobalBounds();
	sf::Rect<int> rect(
		static_cast<int>(globalBounds.left),
		static_cast<int>(globalBounds.top),
		static_cast<int>(globalBounds.width),
		static_cast<int>(globalBounds.height)
	);
	return rect;
}
Button::Button(const sf::Vector2f position, std::string const& filepath, std::string const& buttonName) :_font(AssetManager::GetFont("Font/pixel.ttf")) {
	_type = Icon;
	name = buttonName;

	sf::Texture& texture = AssetManager::GetTexture(filepath);
	_sprite.setTexture(texture);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
	_position = position;

	_rect = getSpriteBounds(_sprite);
}
Button::Button(const sf::Vector2f position, const std::wstring& str, std::string const& buttonName) :_font(AssetManager::GetFont("Font/pixel.ttf")) {
	_type = Text;
	name = buttonName;

	_position = position;

	sf::Texture& texture0 = AssetManager::GetTexture("Image/IconButton/item_0.png");
	_icon_unpointed.setTexture(texture0);
	_icon_unpointed.setOrigin(_icon_unpointed.getLocalBounds().width / 2, _icon_unpointed.getLocalBounds().height / 2);
	//	_icon_unpointed.setPosition(position.x, position.y);

	sf::Texture& texture1 = AssetManager::GetTexture("Image/IconButton/item_1.png");
	_icon_pointed.setTexture(texture1);
	_icon_pointed.setOrigin(_icon_pointed.getLocalBounds().width / 2, _icon_pointed.getLocalBounds().height / 2);
	//	_icon_pointed.setPosition(position.x, position.y);

	_text.setString(str);
	_text.setFont(_font);
	_text.setCharacterSize(36);
	_text.setFillColor(sf::Color::White);
	_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
	//	_text.setPosition(position.x, position.y - 10);

	_rect = getSpriteBounds(_icon_unpointed);

}

bool Button::isPointed(sf::Vector2i clickPosition) {
	if (_type == Icon) {
		_rect = getSpriteBounds(_sprite);
	}
	else {
		_rect = getSpriteBounds(_clickState ? _icon_pointed : _icon_unpointed);
	}
	return _rect.contains(clickPosition);
}

void Button::updateStatus(sf::RenderWindow& window) {
	sf::Vector2i mousePos = getMousePosition(window);
	bool status = isPointed(mousePos);
	if (status != _clickState) {
		printf("button %s is pointed CHANGE  %d\n", this->name.c_str(), status);
		_clickState = status;
		if (_type == Icon) {
			_sprite.setScale(status ? stressFactor : 1.0f, status ? stressFactor : 1.0f);
		}
		else {
			_text.setFillColor(status ? (sf::Color::Black) : (sf::Color::White));
		}

	}
}

void Button::draw(sf::RenderWindow& window) {
	updateStatus(window);
	if (_type == Icon) {
		_sprite.setPosition(_position.x + getWindowStart().x, _position.y + getWindowStart().y);
		window.draw(_sprite);
	}
	else {
		_icon_pointed.setPosition(_position.x + getWindowStart().x, _position.y + getWindowStart().y);
		_icon_unpointed.setPosition(_position.x + getWindowStart().x, _position.y + getWindowStart().y);
		_clickState ? window.draw(_icon_pointed) : window.draw(_icon_unpointed);
		_text.setPosition(_position.x + getWindowStart().x, _position.y - 10 + getWindowStart().y);
		window.draw(_text);
	}
}

Interface::Interface() :_font(AssetManager::GetFont("Font/pixel.ttf")) {
	sf::Texture& texture = AssetManager::GetTexture("Image/Mouse/mouse.png");
	_mouse.setTexture(texture);
}


void Interface::addIconButton(const sf::Vector2f& position, std::string const& filepath, std::string const& name) {
	_buttons.push_back(Button::Button(position, filepath, name));
}
void Interface::addTextButton(const sf::Vector2f& position, const std::wstring& str, std::string const& name) {
	_buttons.push_back(Button::Button(position, str, name));
}

void Interface::setBackground(std::string const& filepath) {
	_backgroundSprite = sf::Sprite(AssetManager::GetTexture(filepath));
}
void Interface::drawBackground(sf::RenderWindow& window) {
	_backgroundSprite.setPosition(sf::Vector2f(Game::view.getCenter().x - Game::GetWindow().getSize().x / 2.0f, Game::view.getCenter().y - Game::GetWindow().getSize().y / 2.0f));
	window.draw(_backgroundSprite);
}
void Interface::drawButton(sf::RenderWindow& window) {
	for (Button& button : _buttons) {
		button.draw(window);
	}
}
void Interface::drawMouse(sf::RenderWindow& window) {
	window.setMouseCursorVisible(false);
	_mouse.setPosition(changeV2itoV2f(getMousePosition(window)).x, changeV2itoV2f(getMousePosition(window)).y);
	window.draw(_mouse);
}
std::string Interface::getClickButtonName(sf::Vector2i clickPosition) {
	for (Button& button : _buttons)
		if (button.isPointed(clickPosition))
			return button.name;
	return "";
}
