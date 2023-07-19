#include "stdafx.h"
#include "Monster.h"
#include "Game.h"
#include "PlayerChick.h"
#include "Animator.h"

Monster::Monster(std::string filename, std::string name) :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity(80.0f),
	health(100.0f),
	maxHealth(100.0f),
	baseDamage(10.0f),
	scores(10.0f),
	lastAttackTime(0.0f),
	_name(name),
	animator(GetSprite())
{
	//Load("images/paddle.png");
	//assert(IsLoaded());

	Load(filename);
	
	sf::Vector2i spriteSize1(100, 85);
	auto& idleAnimation1 = animator.CreateAnimation("Idle", "Image/Capoo/Capoo_8.png", sf::seconds(1), true);

	idleAnimation1.AddFrames(sf::Vector2i(0, 0), spriteSize1, 8);

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
	//std::cout << GetBoundingRect().width << std::endl;
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
}


Monster::~Monster()
{
}

void Monster::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

sf::Vector2f Monster::GetVelocity() const
{
	return _velocity;
}

void Monster::Update(float elapsedTime)
{
	//std::cout << GetPosition().x << " " << GetPosition().y << std::endl;
	sf::Time t = sf::seconds(elapsedTime);
	//if (Game::gameTime.getElapsedTime() < sf::seconds(20))
	animator.Update(t);

	
	// Ѫ�����
	if (health <= 0)
	{
		monsterDie();
	}
	
	// upgrade
	upgrade();

	// chase
	chase();

	// attack
	attack();

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
}

void Monster::getDamage(float damage)
{
	health -= damage;
	// ����������
}

void Monster::monsterDie()
{
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	player->getScore(scores);
	Game::GetMonsterManager().Erase(_name);
	// ����������
	// ����
}

void Monster::upgrade()
{
	sf::Time t = Game::gameTime.getElapsedTime();
	int time = t.asSeconds();
	int cal = pow(time / 50, 0.8);
	baseDamage = 10 + cal;
	// ���٣�����
}

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
	// BUG
	sf::Time t = Game::gameTime.getElapsedTime();
	float time = t.asSeconds();
	if (time - lastAttackTime < 1.0)
	{
		return;
	}
	//std::cout << "TIME:" << time << std::endl;
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	sf::Rect<float> playerRec = player->GetBoundingRect();
	sf::Rect<float> monsterRec = GetBoundingRect();
	if (playerRec.intersects(monsterRec))
	{
		lastAttackTime = time;
		//std::cout << "Attack" << std::endl;
		player->getDamage(baseDamage);
	}
}