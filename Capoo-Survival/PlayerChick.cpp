#include "stdafx.h"
#include "PlayerChick.h"
#include "Game.h"


PlayerChick::PlayerChick() :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity({ 600.0f, 600.0f }),
	health(100.0f),
	maxHealth(100.0f),
	baseDamage(50.0f),
	direction({ -1, 0 }),
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
		direction = { -1, -1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = -30.0f;
		_velocity.y = 30.0f;
		direction = { -1, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = 30.0f;
		_velocity.y = -30.0f;
		direction = { 1, -1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = 30.0f;
		_velocity.y = 30.0f;
		direction = { 1, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity.x = -30.0f;
		_velocity.y = 0.0f;
		direction = { -1, 0 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity.x = 30.0f;
		_velocity.y = 0.0f;
		direction = { 1, 0 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = 0.0f;
		_velocity.y = 30.0f;
		direction = { 0, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = 0.0f;
		_velocity.y = -30.0f;
		direction = { 0, -1 };
	}
	else
	{
		_velocity.x = 0.0f;
		_velocity.y = 0.0f;
	}

	// ÑªÁ¿¼ì²â

	// attack

	// Åö×²¼ì²â

	// score & upgrade

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
	Game::view.setCenter(GetPosition());
	Game::GetWindow().setView(Game::view);
}

void PlayerChick::getDamage(float damage)
{
	health -= damage;
	// ¶¯»­¡¢ÉùÒô
}