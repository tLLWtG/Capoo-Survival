#pragma once

#include "GameObjectManager.h"
#include "SplashScreen.h"
#include "Mainmenu.h"
#include "ObstacleManager.h"
#include "AssetManager.h"
#include "MonsterManager.h"

class Game
{
public:
	static void Start(int frame_per_seconds);
	static sf::RenderWindow& GetWindow();
	static void GetDead();
	static GameObjectManager& GetGameObjectManager();
	static ObstacleManager& GetObstacleManager();
	const static sf::Event& GetInput();
	
	
	//const static sf::Vector2f GetPlayerPosition();

	static sf::View view;
	static sf::Clock gameTime;
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;


	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Dead, Exiting
	};

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowDieScreen();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
	static SplashScreen _splashscreen;
	static Mainmenu _mainmenu;
	static ObstacleManager _obstacleManager;
	static AssetManager _assetManager;
	static MonsterManager _monsterManager;
};
