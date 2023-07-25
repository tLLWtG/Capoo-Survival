#include "stdafx.h"
#include "Monster.h"
#include "Game.h"
#include "PlayerChick.h"
#include "Animator.h"
#include "JumpText.h"

Monster::Monster(std::string filename, std::string name, bool isBoss) :
	_velocity({ 0.0f, 0.0f }),
	lastAttackTime(0.0f),
	_name(name),
	deadTime(0.0f),
	animator(GetSprite()),
	_jumptext(this)
{
	Load(filename);

	if (isBoss)
	{
		sf::Vector2i spriteSize1(300, 255);
		sf::Vector2i spriteSize2(300, 240);
		auto& idleAnimationL = animator.CreateAnimation("IdleL", "Image/Capoo/Capoo_14_L_3x.png", sf::seconds(1), true);
		auto& idleAnimationR = animator.CreateAnimation("IdleR", "Image/Capoo/Capoo_14_R_3x.png", sf::seconds(1), true);
		auto& idleAnimationDL = animator.CreateAnimation("DieIdleL", "Image/Capoo/CapooDie_L_3x.png", sf::seconds(1), true);
		auto& idleAnimationDR = animator.CreateAnimation("DieIdleR", "Image/Capoo/CapooDie_R_3x.png", sf::seconds(1), true);

		idleAnimationL.AddFrames(sf::Vector2i(0, 0), spriteSize1, 14);
		idleAnimationR.AddFrames(sf::Vector2i(0, 0), spriteSize1, 14);
		idleAnimationDL.AddFrames(sf::Vector2i(0, 0), spriteSize2, 45);
		idleAnimationDR.AddFrames(sf::Vector2i(0, 0), spriteSize2, 45);
	}
	else
	{
		sf::Vector2i spriteSize1(100, 85);
		sf::Vector2i spriteSize2(100, 80);
		auto& idleAnimationL = animator.CreateAnimation("IdleL", "Image/Capoo/Capoo_14_L.png", sf::seconds(1), true);
		auto& idleAnimationR = animator.CreateAnimation("IdleR", "Image/Capoo/Capoo_14_R.png", sf::seconds(1), true);
		auto& idleAnimationDL = animator.CreateAnimation("DieIdleL", "Image/Capoo/CapooDie_L.png", sf::seconds(1), true);
		auto& idleAnimationDR = animator.CreateAnimation("DieIdleR", "Image/Capoo/CapooDie_R.png", sf::seconds(1), true);

		idleAnimationL.AddFrames(sf::Vector2i(0, 0), spriteSize1, 14);
		idleAnimationR.AddFrames(sf::Vector2i(0, 0), spriteSize1, 14);
		idleAnimationDL.AddFrames(sf::Vector2i(0, 0), spriteSize2, 45);
		idleAnimationDR.AddFrames(sf::Vector2i(0, 0), spriteSize2, 45);
	}


	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
	
	srand(clock());
	sf::Vector2f birthpos = { float(rand() % 1100), float(rand() % 600) };
	while (5 != 3)
	{
		if ((birthpos.x > 900 || birthpos.x < 200) && (birthpos.y > 450 || birthpos.y < 150))
			break;
		birthpos = { float(rand() % 1100), float(rand() % 600) };
	}
	birthpos.x -= 550;
	birthpos.y -= 300;
	GetSprite().setPosition(birthpos.x + Game::view.getCenter().x, birthpos.y + Game::view.getCenter().y);


	sf::Time t = Game::gameTime.getElapsedTime();
	int time = t.asSeconds();
	time += Game::addTime;
	int cal = pow(time / 10, 0.95);
	if (isBoss)
	{
		baseDamage = 20 + cal;
		_maxVelocity = 80.0f + cal;
		health = 200.0f + cal * 10;
		maxHealth = health;
		scores = 50.0f + cal;
		//GetSprite().setScale(3, 3);
	}
	else
	{
		baseDamage = 10 + cal / 3;
		_maxVelocity = 80.0f + cal;
		health = 100.0f + cal * 5;
		maxHealth = health;
		scores = 10.0f + cal;
	}

}


Monster::~Monster()
{
}

void Monster::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
	_jumptext.Draw(rw);
}

sf::Vector2f Monster::GetVelocity() const
{
	return _velocity;
}

void Monster::Update(float elapsedTime)
{	
	sf::Time t = sf::seconds(elapsedTime);
	animator.Update(t);
	
	if (health <= 0)
	{
		monsterDie();
		return;
	}

	if (_direction == Left && GetPosition().x < Game::view.getCenter().x)
	{
		animator.SwitchAnimation("IdleR");
		_direction = Right;
	}
	else if (_direction == Right && GetPosition().x > Game::view.getCenter().x)
	{
		animator.SwitchAnimation("IdleL");
		_direction = Left;
	}

	chase();

	attack();

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);

	_jumptext.Update(elapsedTime);
}

void Monster::getDamage(float damage)
{
	health -= damage;
	// 声音、数值显示
	_jumptext.SetDamage((int)damage);
}

void Monster::monsterDie()
{
	if (fabs(deadTime - 0.0f) < 1e-6)
	{
		sf::Time t = Game::gameTime.getElapsedTime();
		float time = t.asSeconds();
		deadTime = time;
		PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
		player->getScore(scores);
		if (_direction == Right)
			animator.SwitchAnimation("DieIdleR");
		else animator.SwitchAnimation("DieIdleL");
		return;
	}
	else
	{
		sf::Time t = Game::gameTime.getElapsedTime();
		float time = t.asSeconds();
		if (time - deadTime < 1.0)
		{
			return;
		}
	}

	Game::GetMonsterManager().Erase(_name);
}

//void Monster::upgrade()
//{
//	sf::Time t = Game::gameTime.getElapsedTime();
//	int time = t.asSeconds();
//	int cal = pow(time / 50, 0.8);
//	baseDamage = 10 + cal;
//	// 移速，生命
//}

void Monster::chase()
{
	sf::Vector2f goalPositon = Game::view.getCenter();
	float xd = goalPositon.x - GetPosition().x;
	float yd = goalPositon.y - GetPosition().y;
	float d = sqrtf(xd * xd + yd * yd);
	_velocity.x = _maxVelocity * xd / d;
	_velocity.y = _maxVelocity * yd / d;
}

void Monster::attack()
{
	sf::Time t = Game::gameTime.getElapsedTime();
	float time = t.asSeconds();
	if (time - lastAttackTime < 1.0)
	{
		return;
	}
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	sf::Rect<float> playerRec = player->GetBoundingRect();
	sf::Rect<float> monsterRec = GetBoundingRect();
	if (playerRec.intersects(monsterRec))
	{
		lastAttackTime = time;
		player->getDamage(baseDamage);
	}
}

Monster::Direction _direction;