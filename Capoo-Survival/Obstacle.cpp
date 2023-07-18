#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"
Obstacle::Obstacle(std::string filename)
{
	float HalfWidth = GetWidth()/2;
	float HalfHeight = GetHeight()/2;
	float ScreenHalfHeight = Game::SCREEN_HEIGHT / 2;
	float ScreenHalfWidth = Game::SCREEN_WIDTH / 2;

	Load(filename);
	assert(IsLoaded());

	srand(clock());

	GetSprite().setOrigin(HalfWidth,HalfHeight);
	SetPosition(rand()%(int)ScreenHalfWidth, rand()%(int)ScreenHalfHeight);
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
	// 越界重新设置位置
	if (fabs(playerposx - nowposx) > ObsHalfWidth + ScreenHalfWidth ||
		fabs(playerposy - nowposy) > ObsHalfHeight + ScreenHalfHeight)
	{

		int x = rand() % (2 * (int)ScreenHalfWidth);
		int y = rand() % (2 * (int)ScreenHalfHeight);
		bool isOk = true;
		while (1)
		{
			x = playerposx + rand() % ((int)ScreenHalfWidth );
			y = playerposy + rand() % ((int)ScreenHalfHeight);

			std::set<std::string>& myset = Game::GetObstacleManager().GetObstacleSet();
			
			GameObjectManager& gamemanager = Game::GetGameObjectManager();

			for (std::set<std::string>::iterator it = myset.begin(); it != myset.end(); it++)
			{
				auto alrobs = gamemanager.Get((*it));
				int arlx = alrobs->GetPosition().x;
				int arly = alrobs->GetPosition().y;

				if ((x - arlx) * (x - arlx) + (y - arly) * (y - arly) < 200)isOk = false;
			}

			this->GetSprite().setPosition(x, y);
			if (isOk)break;
		}
	}

}

void Obstacle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}