#include "stdafx.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "Game.h"
MonsterManager::MonsterManager()
{
	cnt = 0;
	lastUpdate = 0.0f;
}

MonsterManager::~MonsterManager()
{

}

void MonsterManager::Update()
{
	sf::Time t = Game::gameTime.getElapsedTime();
	float time = t.asSeconds();
	if (time - lastUpdate < 2.7)
	{
		return;
	}
	lastUpdate = time;

	int height = Game::SCREEN_HEIGHT;
	int width = Game::SCREEN_WIDTH;

	std::string filename = "Image/Capoo/Capoo.png";
	std::string name = "monster" + std::to_string(++cnt);

	Monster* monster = new Monster(filename, name);
	MonsterSet.insert(name);
	Game::GetGameObjectManager().Add(name, monster);
}

void MonsterManager::Erase(std::string name)
{
	Game::GetGameObjectManager().Remove(name);
	MonsterSet.erase(name);
}

std::set<std::string>& MonsterManager::GetMonsterSet()
{
	return MonsterSet;
}
