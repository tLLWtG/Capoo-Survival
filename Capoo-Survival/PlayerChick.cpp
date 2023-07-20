#include "stdafx.h"
#include "PlayerChick.h"
#include "Game.h"
#include "GameObjectManager.h"


PlayerChick::PlayerChick() :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity(150.0f),
	health(200.0f),
	maxHealth(200.0f),
	baseDamage(50.0f),
	direction({ -1, 0 }),
	scores(0),
	animator(GetSprite())
{
	
	Load("Image/Chick/Chick.png");
	//assert(IsLoaded());

	sf::Vector2i spriteSize1(73, 74);
	
	auto& idleAnimation1 = animator.CreateAnimation("Idle", "Image/Chick/PlayerChick.png", sf::seconds(0.5), true);

	idleAnimation1.AddFrames(sf::Vector2i(0, 0), spriteSize1, 60);
	
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

	sf::Time t = sf::seconds(elapsedTime);
	
	animator.Update(t);

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
	if (health > maxHealth)
	{
		health = maxHealth;
	}
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
	float pLeft = playerRec.left;
	float pRight = pLeft + playerRec.width;
	float pTop = playerRec.top;
	float pBottom = pTop + playerRec.height;

	std::set<std::string>& obs = Game::GetObstacleManager().GetObstacleSet();
	for (auto& x : obs)
	{
		sf::Rect<float> obRect = Game::GetGameObjectManager().Get(x)->GetBoundingRect();
		if (playerRec.intersects(obRect))
		{
			/*_velocity.x = -_velocity.x;
			_velocity.y = -_velocity.y;*/
			float xLeft = obRect.left;
			float xRight = xLeft + obRect.width;
			float xTop = obRect.top;
			float xBottom = xTop + obRect.height;

			if (pLeft < xRight && pRight > xRight && ((pTop > xTop && pTop < xBottom) && (pBottom > xTop && pBottom < xBottom)))
			{
				_velocity.x = abs(_velocity.x);
				GetSprite().move(2, 0);
			}
			else if (pLeft < xRight && pRight > xRight && ((pTop < xTop && pBottom > xBottom)))
			{
				_velocity.x = abs(_velocity.x);
				GetSprite().move(2, 0);
			}
			else if (pLeft < xRight && pRight > xRight && ((pTop > xTop && pTop < xBottom)))
			{
				_velocity.x = abs(_velocity.x);
				_velocity.y = abs(_velocity.y);
				GetSprite().move(2, 2);
			}
			else if (pLeft < xRight && pRight > xRight && ((pBottom > xTop && pBottom < xBottom)))
			{
				_velocity.x = abs(_velocity.x);
				_velocity.y = -abs(_velocity.y);
				GetSprite().move(2, -2);
			}
			//
			else if (pRight > xLeft && pLeft < xLeft && ((pTop > xTop && pTop < xBottom) && (pBottom > xTop && pBottom < xBottom)))
			{
				_velocity.x = -abs(_velocity.x);
				GetSprite().move(-2, 0);
			}
			else if (pRight > xLeft && pLeft < xLeft && ((pTop < xTop && pBottom > xBottom)))
			{
				_velocity.x = -abs(_velocity.x);
				GetSprite().move(-2, 0);
			}
			else if (pRight > xLeft && pLeft < xLeft && ((pTop > xTop && pTop < xBottom)))
			{
				_velocity.x = -abs(_velocity.x);
				_velocity.y = abs(_velocity.y);
				GetSprite().move(-2, 2);
			}
			else if (pRight > xLeft && pLeft < xLeft && ((pBottom > xTop && pBottom < xBottom)))
			{
				_velocity.x = -abs(_velocity.x);
				_velocity.y = -abs(_velocity.y);
				GetSprite().move(-2, -2);
			}
			

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