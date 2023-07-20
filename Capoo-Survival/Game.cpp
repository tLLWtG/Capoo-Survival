#include "stdafx.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerChick.h"
#include "SplashScreen.h"
#include "Mainmenu.h"
#include "ObstacleManager.h"
#include "Animator.h"
#include "MonsterManager.h"
#include "Sword.h"
#include "DieScreen.h"
#include "PlayingLayer.h"


void Game::Start(int frame_per_seconds)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Capoo-Survival!", sf::Style::Titlebar | sf::Style::Close);

	_mainWindow.setFramerateLimit(frame_per_seconds);

	// 在这里初始化游戏内的对象
	_BGM_Mainmenu.openFromFile("Music/BGM_Mainmenu.flac");
	_BGM_Game.openFromFile("Music/BGM_Game.flac");
	PlayerChick* player = new PlayerChick();
	player->SetPosition(0, 0);
	_gameObjectManager.Add("player", player);

	Sword* sword = new Sword();
	sword->SetPosition(0, 0);
	_gameObjectManager.Add("weapon", sword);

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(0, 0));

	_mainWindow.setView(view);


	_gameState = Game::ShowingSplash;


	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}


sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

void Game::GetDead()
{
	_gameState = Dead;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

ObstacleManager& Game::GetObstacleManager()
{
	return Game::_obstacleManager;
}

MonsterManager& Game::GetMonsterManager()
{
	return Game::_monsterManager;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		_BGM_Mainmenu.setLoop(true);
		_BGM_Mainmenu.play();
		ShowMenu();
		_BGM_Mainmenu.stop();
		//std::cout << 1 << std::endl;
		_BGM_Game.setLoop(true);
		_BGM_Game.play();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::Playing:
	{
		_mainWindow.clear(sf::Color(52, 103, 49));

		_monsterManager.Update();
		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);

		_playinglayer.showHP(_mainWindow);

		_mainWindow.display();
		if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
			/* 测试语句：按DI出现DieScreen */
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				_gameState = Game::Dead;
				ShowDieScreen();
			}
		}

		break;
	}
	case Game::Dead:
	{
		ShowDieScreen();
		_BGM_Game.stop();
		break;
	}
	}
}

void Game::ShowSplashScreen()
{
	
	_splashscreen.show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	player->SetPosition(0, 0);
	player->getDamage(-200);
	_monsterManager.lastUpdate = 0.0f;
	std::set<std::string> monsterSet = _monsterManager.GetMonsterSet();
	
	for (auto& x : monsterSet)
	{
		Monster* monster = dynamic_cast<Monster*>(Game::GetGameObjectManager().Get(x));
		monster->monsterDie();
	}
	_monsterManager.cnt = 0;

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(0, 0));

	_mainWindow.setView(view);
	Mainmenu::MenuResult result = _mainmenu.show(_mainWindow);
	switch (result)
	{
	case Mainmenu::Exiting:
		_gameState = Exiting;
		break;
	case Mainmenu::Playing:
		_gameObjectManager.clock.restart();
		_gameState = Playing;
		break;
	}
	Game::gameTime.restart();

}

void Game::ShowDieScreen()
{
	switch (_diescreen.show(_mainWindow))
	{
	case 1: {
		_gameState = ShowingMenu;
		break;
	}
	case 0: {
		_gameState = Exiting;
	}
	default:
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::View Game::view;
SplashScreen Game::_splashscreen;
Mainmenu Game::_mainmenu;
PlayingLayer Game::_playinglayer;
sf::Clock Game::gameTime;
ObstacleManager Game::_obstacleManager;
AssetManager Game::_assetManager;
MonsterManager Game::_monsterManager;
DieScreen Game::_diescreen;
sf::Music Game::_BGM_Mainmenu;
sf::Music Game::_BGM_Game;