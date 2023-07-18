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
	
	float playerposx = Game::view.getCenter().x;
	float playerposy = Game::view.getCenter().y;
	float ScreenHalfHeight = Game::SCREEN_HEIGHT/2;
	float ScreenHalfWidth = Game::SCREEN_WIDTH/2;
	
	srand(clock());
	// Խ����������λ��
	if (fabs(playerposx - nowposx) > ObsHalfWidth + ScreenHalfWidth ||
		fabs(playerposy - nowposy) > ObsHalfHeight + ScreenHalfHeight)
	{
		
		int x = rand() % (2 * (int)ScreenHalfWidth);
		int y = rand() % (2 * (int)ScreenHalfHeight);
		bool isOk = true;
		while (1)
		{
			x = rand() % (2 * (int)ScreenHalfWidth);
			y = rand() % (2 * (int)ScreenHalfHeight);

			auto myset = Game::GetObstacleManager().GetObstacleSet();
			auto gamemanager = Game::GetGameObjectManager();
			for (std::set<std::string>::iterator it = myset.begin(); it != myset.end(); it++)
			{
				auto alrobs = gamemanager.Get((*it));
				int arlx = alrobs->GetPosition().x;
				int arly = alrobs->GetPosition().y;

				if ((x - arlx) * (x - arlx) + (y - arly) * (y - arly) < 200)isOk = false;
			}

			if (isOk)break;
		}
		this->GetSprite().setPosition(x,y);
	}

}

void Obstacle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}