#include "Player.h"

void Player::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(_shape, states);
}

Player::Player() : _shape(sf::Vector2f(100, 100))
{
}

void Player::update(sf::Time deltaTime)
{
}