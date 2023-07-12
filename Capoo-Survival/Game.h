#pragma once

#include "GameObjectManager.h"

class Game
{
public:
	static void Start(int frame_per_seconds);
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	const static GameObjectManager& GetGameObjectManager();

	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
};