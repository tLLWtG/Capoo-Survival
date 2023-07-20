#pragma once

class JumpText : public Interface
{
public:
	JumpText(int damage, sf::Vector2f postion);
	void showDamage(sf::RenderWindow& window);

private:
	sf::Text _damegeText;
	sf::Vector2f _position;
};