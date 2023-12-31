#include "stdafx.h"
#include "PlayerChick.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Sword.h"


PlayerChick::PlayerChick() :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity(200.0f),
	health(200.0f),
	maxHealth(200.0f),
	baseDamage(5.0f),
	direction({ -1, 0 }),
	lastHeal(0.0f),
	scores(0),
	animator(GetSprite()),
	lastHurt(-1.0f),
	_jumptext(this)
{

	Load("Image/Chick/Chick.png");

	voice_hurt.openFromFile("Music/Hurt.flac");
	hurt_tex.loadFromFile("Image/Animator/hurt.png");
	image_hurt.setTexture(hurt_tex);
	image_hurt.setOrigin(image_hurt.getLocalBounds().width / 2, image_hurt.getLocalBounds().height / 2);

	sf::Vector2i spriteSize1(73, 74);

	auto& idleAnimation1 = animator.CreateAnimation("Idle", "Image/Chick/PlayerChick.png", sf::seconds(0.5), true);

	idleAnimation1.AddFrames(sf::Vector2i(0, 0), spriteSize1, 60);

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);

	_skill = new Skill_Spurt();
}


PlayerChick::~PlayerChick()
{
}

void PlayerChick::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
	_jumptext.Draw(rw);
	_skill->Draw(rw);
}

sf::Vector2f PlayerChick::GetVelocity() const
{
	return _velocity;
}

void PlayerChick::Update(float elapsedTime)
{

	sf::Time t = sf::seconds(elapsedTime);

	animator.Update(t);
	_jumptext.Update(elapsedTime);
	_skill->Update(elapsedTime);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_skill->Fire();

	if (health > maxHealth)
	{
		health = maxHealth;
	}
	if (health <= 0)
	{
		health = 200;
		maxHealth = 200;
		playerDie();
	}

	// fire in weapon
	showHurt();

	boundCheck();

	upgrade();

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
	Game::view.setCenter(GetPosition());
	Game::GetWindow().setView(Game::view);
	image_hurt.setPosition(GetPosition());
}

void PlayerChick::playerDie()
{
	scores = 0;
	Game::GetDead();
}

void PlayerChick::getDamage(float damage)
{
	health -= damage;
	_jumptext.SetDamage((int)damage);
	if (damage > 0)
	{
		voice_hurt.play();
		if (Game::gameTime.getElapsedTime().asSeconds() - lastHurt > 0.5f)
		{
			lastHurt = Game::gameTime.getElapsedTime().asSeconds();
		}
	}

	// ��������ֵ��ʾ
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
	int cal = pow(scores / 100, 0.95);
	cal /= 3;
	baseDamage = 5 + cal * 3;
	maxHealth = 200.0f + cal * 5;
	_maxVelocity = 200.0f + cal * 2;

	if (cal >= 30)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(Game::GetGameObjectManager().Get("weapon"));
		weapon->setSize(2.7f);
	}
	else if (cal >= 15)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(Game::GetGameObjectManager().Get("weapon"));
		weapon->setSize(2.5f);
	}
	else if (cal >= 5)
	{
		Weapon* weapon = dynamic_cast<Weapon*>(Game::GetGameObjectManager().Get("weapon"));
		weapon->setSize(2.3f);
	}

	sf::Time t = Game::gameTime.getElapsedTime();
	float time = t.asSeconds();
	if (time - lastHeal < 1.0)
	{
		return;
	}
	if (health + 3 <= maxHealth)
		getDamage(-3);
	else
		getDamage(health - maxHealth);
	lastHeal = time;
}

void PlayerChick::showHurt()
{
	float diff = Game::gameTime.getElapsedTime().asSeconds() - lastHurt;
	if (diff < 0 || diff > 0.5)
	{
		//image_hurt.setColor(sf::Color::Color(0, 0, 0, 0));
		sf::Color temp = image_hurt.getColor();
		temp.a = 0;
		image_hurt.setColor(temp);
		return;
	}
	float cal = 255 * (-16 * diff * diff + 8 * diff);
	//std::cout << cal << std::endl;
	//image_hurt.setColor(sf::Color::Color(168, 15, 2, cal));
	sf::Color temp = image_hurt.getColor();
	temp.a = cal;
	image_hurt.setColor(temp);
	//Game::GetWindow().draw(image_hurt);
}

sf::Music PlayerChick::voice_hurt;