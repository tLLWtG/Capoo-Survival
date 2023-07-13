#include "stdafx.h"
#include "Monster.h"
#include "Game.h"


Monster::Monster() :
	_velocity({ 0.0f, 0.0f }),
	_maxVelocity({ 400.0f, 400.0f }),
	health(100.0f),
	maxHealth(100.0f),
	baseDamage(10.0f),
	score(10)
{
	//Load("images/paddle.png");
	//assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);

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
	// ÑªÁ¿¼ì²â

	// Chase

	// Åö×²¼ì²â

	// attack

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
}

void Monster::getDamage(float damage)
{
	health -= damage;
	// ¶¯»­¡¢ÉùÒô
}