#include "PlayingLayer.h"
#include "PlayerChick.h"
#include "Game.h"

PlayingLayer::PlayingLayer() {
	_hp_text.setFont(_font);
	_hp_text.setCharacterSize(42);
	_hp_text.setFillColor(sf::Color::White);
	_hp_text.setStyle(sf::Text::Style::Bold);
	_hp_text.setOutlineColor(sf::Color::Black);
	_hp_text.setOutlineThickness(2.0f);
	_hp_text.setString("HP: ");

	_hp_value.setFont(_font);
	_hp_value.setCharacterSize(42);
	_hp_value.setFillColor(sf::Color::White);
	_hp_value.setStyle(sf::Text::Style::Bold);
	_hp_value.setOutlineColor(sf::Color::Black);
	_hp_value.setOutlineThickness(2.0f);
}

void PlayingLayer::showHP(sf::RenderWindow& window) {
	_hp_text.setPosition(getWindowStart().x + 30, getWindowStart().y + 30);
	window.draw(_hp_text);

	const int precision = 1;
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));

	std::string healthValue = (std::to_string(player->health));
	size_t dotPosition = healthValue.find('.');
	if (dotPosition != std::string::npos && dotPosition + precision + 1 < healthValue.size())
		healthValue = healthValue.substr(0, dotPosition + precision + 1);

	std::string maxValue = (std::to_string(player->maxHealth));
	dotPosition = maxValue.find('.');
	if (dotPosition != std::string::npos && dotPosition + precision + 1 < maxValue.size())
		maxValue = maxValue.substr(0, dotPosition + precision + 1);

	_hp_value.setString(healthValue+" / "+maxValue);
	_hp_value.setPosition(_hp_text.getGlobalBounds().left+_hp_text.getGlobalBounds().width, getWindowStart().y + 30);
	window.draw(_hp_value);
}