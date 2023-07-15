#pragma once

#include "GameObjectManager.h"
#include "SplashScreen.h"
#include "Mainmenu.h"

class Game
{
public:
	static void Start(int frame_per_seconds);
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	const static GameObjectManager& GetGameObjectManager();
	const static sf::Vector2f GetPlayerPosition();
	
	static sf::View view;
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;


	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
	static SplashScreen _splashscreen;
	static Mainmenu _mainmenu;
};
