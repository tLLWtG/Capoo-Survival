#include "stdafx.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Game.h"
MonsterManager::MonsterManager()
{
	cnt = '1';
}

MonsterManager::~MonsterManager()
{

}

void MonsterManager::Update()
{
	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;

	std::string filename = "Image/Capoo/Capoo.png";
	std::string name = "monster";

	Monster* monster = new Monster(filename, name + '1');

	Game::GetGameObjectManager().Add(name + '1', monster);
}

char MonsterManager::cnt = 0;
