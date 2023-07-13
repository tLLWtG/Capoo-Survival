#include "stdafx.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerChick.h"

void Game::Start(int frame_per_seconds)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

	_mainWindow.setFramerateLimit(frame_per_seconds);

	// 在这里初始化游戏内的对象
	PlayerChick* player = new PlayerChick();
	player->SetPosition(0, 0);
	_gameObjectManager.Add("player", player);

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

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::Playing:
	{
		_mainWindow.clear(sf::Color(0, 0, 0));

		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);

		_mainWindow.display();
		if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
		}

		break;
	}
	}
}

void Game::ShowSplashScreen()
{
	//SplashScreen splashScreen;
	//splashScreen.Show(_mainWindow);
	//_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	//MainMenu mainMenu;
	//MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	//switch (result)
	//{
	//case MainMenu::Exit:
	//	_gameState = Exiting;
	//	break;
	//case MainMenu::Play:
	//	_gameObjectManager.clock.restart();
	//	_gameState = Playing;
	//	break;
	//}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::View Game::view;