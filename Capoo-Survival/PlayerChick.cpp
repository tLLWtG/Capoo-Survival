#include "stdafx.h"
#include "PlayerChick.h"
#include "Game.h"
#include "GameObjectManager.h"

PlayerChick::PlayerChick() :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity(150.0f),
	health(100.0f),
	maxHealth(200.0f),
	baseDamage(50.0f),
	direction({ -1, 0 }),
	scores(0)
{
	Load("Image/Chick/Chick.png");
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
		_velocity.x = -_maxVelocity * 0.707;
		_velocity.y = -_maxVelocity * 0.707;
		direction = { -1, -1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = -_maxVelocity * 0.707;
		_velocity.y = _maxVelocity * 0.707;
		direction = { -1, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = _maxVelocity * 0.707;
		_velocity.y = -_maxVelocity * 0.707;
		direction = { 1, -1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = _maxVelocity * 0.707;
		_velocity.y = _maxVelocity * 0.707;
		direction = { 1, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity.x = -_maxVelocity;
		_velocity.y = 0.0f;
		direction = { -1, 0 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity.x = _maxVelocity;
		_velocity.y = 0.0f;
		direction = { 1, 0 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity.x = 0.0f;
		_velocity.y = _maxVelocity;
		direction = { 0, 1 };
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_velocity.x = 0.0f;
		_velocity.y = -_maxVelocity;
		direction = { 0, -1 };
	}
	else
	{
		_velocity.x = 0.0f;
		_velocity.y = 0.0f;
	}

	// ÑªÁ¿¼ì²â

	if (health <= 0)
	{
		playerDie();
	}

	// fire in weapon

	// Åö×²¼ì²â
	boundCheck();

	// score & upgrade
	upgrade();

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
	Game::view.setCenter(GetPosition());
	Game::GetWindow().setView(Game::view);
}

void PlayerChick::playerDie()
{
	Game::GetDead();
}

void PlayerChick::getDamage(float damage)
{
	health -= damage;
	// ¶¯»­¡¢ÉùÒô
}

void PlayerChick::getScore(float score)
{
	scores += score;
}

void PlayerChick::boundCheck()
{
	sf::Rect<float> playerRec = GetBoundingRect();
	std::set<std::string>& obs = Game::GetObstacleManager().GetObstacleSet();
	for (auto& x : obs)
	{
		sf::Rect<float> obRect = Game::GetGameObjectManager().Get(x)->GetBoundingRect();
		if (playerRec.intersects(obRect))
		{
			_velocity.x = -_velocity.x;
			_velocity.y = -_velocity.y;
			break;
		}
	}
}

void PlayerChick::upgrade()
{
	int cal = pow(scores / 100, 0.8);
	baseDamage = 50 + cal;
	// ÒÆËÙ£¬ÉúÃü
}