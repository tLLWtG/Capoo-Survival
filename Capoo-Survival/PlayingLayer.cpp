#include "PlayingLayer.h"
#include "PlayerChick.h"
#include "Game.h"
#include "Skill.h"

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

	_cd_text.setFont(_font);
	_cd_text.setCharacterSize(42);
	_cd_text.setFillColor(sf::Color::White);
	_cd_text.setStyle(sf::Text::Style::Bold);
	_cd_text.setOutlineColor(sf::Color::Black);
	_cd_text.setOutlineThickness(2.0f);
	_cd_text.setString("SKILL CD: ");

	_cd_value.setFont(_font);
	_cd_value.setCharacterSize(42);
	_cd_value.setFillColor(sf::Color::White);
	_cd_value.setStyle(sf::Text::Style::Bold);
	_cd_value.setOutlineColor(sf::Color::Black);
	_cd_value.setOutlineThickness(2.0f);

	_score_text.setFont(_font);
	_score_text.setCharacterSize(42);
	_score_text.setFillColor(sf::Color::White);
	_score_text.setStyle(sf::Text::Style::Bold);
	_score_text.setOutlineColor(sf::Color::Black);
	_score_text.setOutlineThickness(2.0f);
	_score_text.setString("Score: ");

	_score_value.setFont(_font);
	_score_value.setCharacterSize(42);
	_score_value.setFillColor(sf::Color::White);
	_score_value.setStyle(sf::Text::Style::Bold);
	_score_value.setOutlineColor(sf::Color::Black);
	_score_value.setOutlineThickness(2.0f);
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

	_hp_value.setString(healthValue + " / " + maxValue);
	_hp_value.setPosition(_hp_text.getGlobalBounds().left + _hp_text.getGlobalBounds().width, getWindowStart().y + 30);
	window.draw(_hp_value);
}

void PlayingLayer::showCD(sf::RenderWindow& window) {
	_cd_text.setPosition(getWindowStart().x + 30, getWindowStart().y + 80);
	window.draw(_cd_text);

	if (Skill::remainingWaitingTime <= 0.0f) {
		_cd_value.setString("ok!");
		_cd_value.setPosition(_cd_text.getGlobalBounds().left + _cd_text.getGlobalBounds().width, getWindowStart().y + 80);
	}
	else {
		const int precision = 1;
		
		std::string skillValue = (std::to_string(Skill::remainingWaitingTime));
		size_t dotPosition = skillValue.find('.');
		if (dotPosition != std::string::npos && dotPosition + precision + 1 < skillValue.size())
			skillValue = skillValue.substr(0, dotPosition + precision + 1);

		std::string maxValue = (std::to_string(Skill::cdTime));
		dotPosition = maxValue.find('.');
		if (dotPosition != std::string::npos && dotPosition + precision + 1 < maxValue.size())
			maxValue = maxValue.substr(0, dotPosition + precision + 1);

		_cd_value.setString(skillValue + " / " + maxValue);
		_cd_value.setPosition(_cd_text.getGlobalBounds().left + _cd_text.getGlobalBounds().width, getWindowStart().y + 80);
	}
	window.draw(_cd_value);
}


void PlayingLayer::showSCORE(sf::RenderWindow& window) {

	const int precision = 1;

	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	std::string scoreValue = (std::to_string(player->scores));
	size_t dotPosition = scoreValue.find('.');
	if (dotPosition != std::string::npos && dotPosition + precision + 1 < scoreValue.size())
		scoreValue = scoreValue.substr(0, dotPosition + precision + 1);

	_score_value.setString(scoreValue);

	_score_text.setPosition(getWindowStart().x + 1280 - _score_text.getLocalBounds().width - _score_value.getLocalBounds().width - 30, getWindowStart().y + 30);
	//	_score_text.setPosition(getWindowStart().x + 640, getWindowStart().y + 30);
	_score_value.setPosition(_score_text.getGlobalBounds().left + _score_text.getGlobalBounds().width, getWindowStart().y + 30);

	window.draw(_score_text);
	window.draw(_score_value);
}
