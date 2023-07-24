#pragma once

#include "GameObjectManager.h"
#include "SplashScreen.h"
#include "Mainmenu.h"
#include "ObstacleManager.h"
#include "BackGroundManager.h"
#include "AssetManager.h"
#include "MonsterManager.h"
#include "DieScreen.h"
#include "PlayingLayer.h"
#include "PauseScreen.h"

class Game
{
public:
	static void Start(int frame_per_seconds);
	static sf::RenderWindow& GetWindow();
	static void GetDead();
	static GameObjectManager& GetGameObjectManager();
	static ObstacleManager& GetObstacleManager();
	static MonsterManager& GetMonsterManager();
	const static sf::Event& GetInput();

	//const static sf::Vector2f GetPlayerPosition();

	static sf::View view;
	static sf::Clock gameTime;
	static float addTime;
	const static int SCREEN_WIDTH = 1280;
	const static int SCREEN_HEIGHT = 720;


	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Loading, Dead, Exiting
	};

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	static void ShowDieScreen();
	static void ShowPauseScreen();
	static void SaveArchive();
	static void LoadArchive();

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
	static SplashScreen _splashscreen;
	static Mainmenu _mainmenu;
	static DieScreen _diescreen;
	static PauseScreen _pausescreen;
	static PlayingLayer _playinglayer;
	static ObstacleManager _obstacleManager;
	static AssetManager _assetManager;
	static MonsterManager _monsterManager;
	static BackGroundManager _backgroundManager;
	static sf::Music _BGM_Mainmenu;
	static sf::Music _BGM_Game;
	
};
