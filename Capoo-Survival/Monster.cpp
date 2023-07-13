#include "stdafx.h"
#include "Monster.h"
#include "Game.h"


Monster::Monster() :
	_velocity({ 0, 0 }),
	_maxVelocity({ 400.0f, 400.0f }),
	health(100),
	maxHealth(100)
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
	// Chase

	// Åö×²¼ì²â

	// attack

	GetSprite().move(_velocity.x * elapsedTime, _velocity.y * elapsedTime);
}