#include "Obstacle.h"

char Obstacle::cnt = '1';

Obstacle::Obstacle()
{
	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;

	std::string filename = "images/test0.png";

	filename.erase(filename.begin() + 11);
	filename.insert(filename.begin() + 11, cnt);
	Load(filename);
	assert(IsLoaded());
	GetSprite().setOrigin(rand() % height - 200, rand() % width - 300);
	cnt++;
}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
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