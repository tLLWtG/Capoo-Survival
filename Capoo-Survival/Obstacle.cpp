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

	float playerposx = Game::view.getCenter().x;
	float playerposy = Game::view.getCenter().y;
	float ObsHalfWidth = GetWidth() / 2;
	float ObsHalfHeight = GetHeight() / 2;
	int x1, y1, x2, y2, x3, y3;
	int x, y;

	while (1)
	{
		bool isOk = true;
		x1 = playerposx + rand() % ((int)ScreenHalfWidth / 2) + (int)(ScreenHalfWidth);
		y1 = playerposy + rand() % ((int)ScreenHalfHeight * 2) - (int)ScreenHalfHeight;
		x2 = playerposx - rand() % ((int)ScreenHalfWidth / 2) - (int)(ScreenHalfWidth);

		y2 = playerposy + rand() % ((int)ScreenHalfHeight / 2) + (int)(ScreenHalfHeight);
		x3 = playerposx + rand() % ((int)ScreenHalfWidth * 2) - (int)ScreenHalfWidth;
		y3 = playerposy - rand() % ((int)ScreenHalfHeight / 2) - (int)(ScreenHalfHeight);

		std::pair<int, int>Pos[4] = { {x1,y1},{x2,y1},{x3,y2},{x3,y3} };
		int pos = rand() % 4;

		x = Pos[pos].first, y = Pos[pos].second;
		std::set<std::string>& myset = Game::GetObstacleManager().GetObstacleSet();

		GameObjectManager& gamemanager = Game::GetGameObjectManager();

		sf::Rect<float> nowRect = GetBoundingRect();
		nowRect.top = y;
		nowRect.left = x;
		for (std::set<std::string>::iterator it = myset.begin(); it != myset.end(); it++)
		{
			auto alrobs = gamemanager.Get((*it));
			sf::Rect<float> haveRect = alrobs->GetBoundingRect();
			if (haveRect == nowRect)continue;
			if (nowRect.intersects(haveRect) ||
				haveRect.contains(x, y) ||
				haveRect.contains(x + ObsHalfHeight, y + ObsHalfHeight) ||
				haveRect.contains(x + ObsHalfHeight * 2, y + 2 * ObsHalfHeight) ||
				haveRect.contains(x + ObsHalfHeight * 2, y + ObsHalfHeight) ||
				haveRect.contains(x + ObsHalfHeight, y + 2 * ObsHalfHeight))
				isOk = false;

		}

		if (isOk)break;
	}
	this->GetSprite().setPosition(x, y);
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
	if (fabs(playerposx - nowposx) > ObsHalfWidth*2 + ScreenHalfWidth*2 ||
		fabs(playerposy - nowposy) > ObsHalfHeight*2 + ScreenHalfHeight*2)
	{

		int x1, y1, x2, y2, x3, y3;
		int x, y;
		
		while (1)
		{
			bool isOk = true;
			x1 = playerposx + rand() % ((int)ScreenHalfWidth / 2 )+ (int)(ScreenHalfWidth);
			y1 = playerposy + rand() % ((int)ScreenHalfHeight * 2 )- (int)ScreenHalfHeight;
			x2 = playerposx - rand() % ((int)ScreenHalfWidth / 2) - (int)(ScreenHalfWidth);
			
			y2 = playerposy + rand() %( (int)ScreenHalfHeight / 2 )+ (int)(ScreenHalfHeight);
			x3 = playerposx + rand() % ((int)ScreenHalfWidth * 2) - (int)ScreenHalfWidth;
			y3 = playerposy - rand() % ((int)ScreenHalfHeight / 2) - (int)(ScreenHalfHeight);

			std::pair<int, int>Pos[4] = { {x1,y1},{x2,y1},{x3,y2},{x3,y3} };
			int pos = rand() % 4;

			x = Pos[pos].first, y = Pos[pos].second;
			std::set<std::string>& myset = Game::GetObstacleManager().GetObstacleSet();
			
			GameObjectManager& gamemanager = Game::GetGameObjectManager();

			sf::Rect<float> nowRect = GetBoundingRect();
			nowRect.top = y;
			nowRect.left = x;
			for (std::set<std::string>::iterator it = myset.begin(); it != myset.end(); it++)
			{
				auto alrobs = gamemanager.Get((*it));
				sf::Rect<float> haveRect = alrobs->GetBoundingRect();
				if (haveRect == nowRect)continue;
				if (nowRect.intersects(haveRect)||
					haveRect.contains(x,y)||
					haveRect.contains(x+ObsHalfHeight,y+ObsHalfHeight)||
					haveRect.contains(x + ObsHalfHeight*2, y + 2*ObsHalfHeight)||
					haveRect.contains(x + ObsHalfHeight * 2, y + ObsHalfHeight)||
					haveRect.contains(x + ObsHalfHeight , y + 2 * ObsHalfHeight))
					isOk = false;
				
			}

			if (isOk)break;
		}
		this->GetSprite().setPosition(x, y);
	}

}

void Obstacle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}