#include "stdafx.h"
#include "Interface.h"
#include "DamageText.h"

DamageText::DamageText(int damage, sf::Vector2f position)
{
	_damegeText.setFont(_font);
	_damegeText.setCharacterSize(42);
	_damegeText.setFillColor(sf::Color::White);
	_damegeText.setStyle(sf::Text::Style::Bold);
	_damegeText.setOutlineColor(sf::Color::Black);
	_damegeText.setOutlineThickness(2.0f);
	_damegeText.setString(std::to_string(damage));
}

void DamageText::showDamage(sf::RenderWindow& window)
{

}