#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"
Obstacle::Obstacle(std::string filename)
{
	float ScreenHalfHeight = Game::SCREEN_HEIGHT;
	float ScreenHalfWidth = Game::SCREEN_WIDTH;

	Load(filename);
	assert(IsLoaded());

	GetSprite().setOrigin(rand() % (2 * (int)ScreenHalfWidth), rand() % (2 * (int)ScreenHalfHeight));
}

Obstacle::~Obstacle()
{

}

sf::Rect<float> Obstacle::GetBoundingRect()const
{
	return VisibleGameObject::GetBoundingRect();
}


void Obstacle::Update(float elapsedTime)
{
	float ObsHalfWidth = GetWidth() / 2;
	float ObsHalfHeight = GetHeight() / 2;
	float nowposx = GetPosition().x;
	float nowposy = GetPosition().y;
	// 此处需要player坐标
	float playerposx = 0;
	float playerposy = 0;
	float ScreenHalfHeight = Game::SCREEN_HEIGHT;
	float ScreenHalfWidth = Game::SCREEN_WIDTH;
	// sf::Vector2f pos = PlayerPaddle::GetPosition();

	// 越界重新设置位置
	if (fabs(playerposx - nowposx) > ObsHalfWidth + ScreenHalfWidth ||
		fabs(playerposy - nowposy) > ObsHalfHeight + ScreenHalfHeight)
	{
		this->GetSprite().setPosition(rand() % (2 * (int)ScreenHalfWidth), rand() % (2 * (int)ScreenHalfHeight));
	}

}

void Obstacle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}