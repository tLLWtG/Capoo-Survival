#pragma once

class DamageText : public Interface
{
public:
	DamageText(int damage, sf::Vector2f postion);
	void showDamage(sf::RenderWindow& window);

private:
	sf::Text _damegeText;
	sf::Vector2f position;
};