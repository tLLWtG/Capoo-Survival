#include "stdafx.h"
#include "PlayerChick.h"
#include "Game.h"


PlayerChick::PlayerChick() :
	_velocity({ 0, 0 }),
	_maxVelocity({ 600.0f, 600.0f }),
	health(100),
	maxHealth(100),
	score(0)
{
	//Load("images/paddle.png");
	//assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);

}


PlayerChick::~PlayerChick()
{
}

void PlayerChick::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

sf::Vector2f PlayerChick::GetVelocity() const
{
	return _velocity;
}

void PlayerChick::Update(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = -30.0f;
		_velocity.y = -30.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = -30.0f;
		_velocity.y = 30.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = 30.0f;
		_velocity.y = -30.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = 30.0f;
		_velocity.y = 30.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity.x = -30.0f;
		_velocity.y = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity.x = 30.0f;
		_velocity.y = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = 0.0f;
		_velocity.y = 30.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = 0.0f;
		_velocity.y = -30.0f;
	}

	// attack

	// Åö×²¼ì²â

	// score & upgrade

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
}