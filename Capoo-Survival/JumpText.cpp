#include "stdafx.h"
#include "Interface.h"
#include "JumpText.h"

JumpText::JumpText(int damage, sf::Vector2f position) :_position(position)
{
	_damegeText.setFont(_font);
	_damegeText.setCharacterSize(24);
	_damegeText.setFillColor(sf::Color::White);
	_damegeText.setStyle(sf::Text::Style::Bold);
	_damegeText.setOutlineColor(sf::Color::Black);
	_damegeText.setOutlineThickness(2.0f);
	_damegeText.setString(std::to_string(damage));
}

void JumpText::showDamage(sf::RenderWindow& window)
{

}