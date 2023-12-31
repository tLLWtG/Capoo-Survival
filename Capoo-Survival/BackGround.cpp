﻿#include "stdafx.h"
#include "BackGround.h"
#include "Game.h"

int BackGround::cnt = 0;

BackGround::BackGround(std::string filename)
{
	float HalfWidth = GetWidth() / 2;
	float HalfHeight = GetHeight() / 2;
	float ScreenHalfHeight = Game::SCREEN_HEIGHT / 2;
	float ScreenHalfWidth = Game::SCREEN_WIDTH / 2;
	float playerposx = Game::view.getCenter().x;
	float playerposy = Game::view.getCenter().y;
	float ObsHalfWidth = GetWidth() / 2;
	float ObsHalfHeight = GetHeight() / 2;

	Load(filename);
	assert(IsLoaded());

	srand(clock());

	GetSprite().setOrigin(HalfWidth, HalfHeight);


	int x = cnt + ScreenHalfWidth + playerposx;
	int y = cnt + ScreenHalfHeight + playerposy;
	cnt += (ScreenHalfHeight + ScreenHalfWidth) / 2;
	GetSprite().setPosition(x, y);
}

BackGround::~BackGround()
{

}

void BackGround::Update(float elapsedTime)
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
			std::set<std::string>& myset = Game::GetBackGroundManager().GetBackGroundSet();
			std::set<std::string>& myobset = Game::GetObstacleManager().GetObstacleSet();

			GameObjectManager& gamemanager = Game::GetGameObjectManager();


			sf::Rect<float> nowRect = GetBoundingRect();
			
			nowRect.top = y;
			nowRect.left = x;
			for (std::set<std::string>::iterator it = myset.begin(); it != myset.end(); it++)
			{
				
				auto alrobs = gamemanager.Get((*it));
				sf::Rect<float> haveRect = alrobs->GetBoundingRect();
				
				for (auto& obs : myobset)
				{
					auto obst = gamemanager.Get(obs);
					int obsx = obst->GetPosition().x;
					int obsy = obst->GetPosition().y;
					if ((obsx - x) * (obsx - x) + (obsy - y) * (obsy - y) < 40000)isOk = false;

				}

				if (haveRect == nowRect)continue;
				if (nowRect.intersects(haveRect) ||
					haveRect.contains(x, y) ||
					haveRect.contains(x + ObsHalfWidth, y + ObsHalfHeight) ||
					haveRect.contains(x + ObsHalfWidth * 2, y + 2 * ObsHalfHeight) ||
					haveRect.contains(x + ObsHalfWidth * 2, y + ObsHalfHeight) ||
					haveRect.contains(x + ObsHalfWidth, y + 2 * ObsHalfHeight))
				{
					isOk = false;
					break;
				}
			}

			if (isOk)break;

		}
		this->GetSprite().setPosition(x, y);
	}

}

void BackGround::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}