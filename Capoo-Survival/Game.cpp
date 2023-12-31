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
#include "BackGroundManager.h"
#include "Archive.h"
#include "SettingScreen.h"

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
BackGroundManager& Game::GetBackGroundManager()
{
	return Game::_backgroundManager;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
	case Game::ShowingMenu:
	{
		_BGM_Game.stop();
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
		_playinglayer.showCD(_mainWindow);
		_playinglayer.showSCORE(_mainWindow);
		_playinglayer.drawMouse(_mainWindow);
		PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
		_mainWindow.draw(player->image_hurt);
		_mainWindow.display();
		if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

		if (currentEvent.type == sf::Event::KeyPressed)
		{
			if (currentEvent.key.code == sf::Keyboard::Escape) ShowPauseScreen();
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
	Mainmenu::MenuResult result = _mainmenu.show(_mainWindow);
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	_monsterManager.lastUpdate = 0.0f;
	_monsterManager.lastWave = 0.0f;
	_monsterManager.lastBoss = 0.0f;
	player->lastHeal = 0.0f;
	player->lastHurt = -1.0f;
	player->SetPosition(0, 0);
	player->maxHealth = 200.0f;
	player->health = 200.0f;
	player->scores = 0;

	std::set<std::string> monsterSet = _monsterManager.GetMonsterSet();

	for (auto& x : monsterSet)
	{
		_gameObjectManager.Remove(x);
	}
	_monsterManager.cnt = 0;
	_monsterManager.GetMonsterSet().clear();

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	view.setCenter(sf::Vector2f(0, 0));

	_mainWindow.setView(view);
	switch (result)
	{
	case Mainmenu::Exiting:
		_gameState = Exiting;
		break;
	case Mainmenu::Playing:
		_gameObjectManager.clock.restart();
		Game::gameTime.restart();
		Game::addTime = 0;
		_gameState = Playing;
		break;
	case Mainmenu::Setting:
		ShowSettingScreen();
		break;
	case Mainmenu::Loading:
		Game::gameTime.restart();
		_gameObjectManager.clock.restart();
		Game::LoadArchive();
		_gameState = Playing;
		break;
	}
}

void Game::ShowSettingScreen() {
	switch (_settingscreen.show(_mainWindow, _gameState == ShowingMenu ? 0 : 1))
	{
	case 0: {
		_gameState = Exiting;
		break;
	}
	case 1: {
		_gameState = ShowingMenu;
		break;
	}
	default:
		break;
	}
}

void Game::ShowPauseScreen() {
	switch (_pausescreen.show(_mainWindow))
	{
	case 0: {
		_gameState = Exiting;
		break;
	}
	case 1: {
		EmptyUpdate();
		_gameState = Playing;
		break;
	}
	case 2: {
		_gameState = ShowingMenu;
		break;
	}
	default:
		break;
	}
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

void Game::SaveArchive()
{
	if (Archive::save())
	{
		// save成功提示
	}
	else
	{
		// save失败提示
	}
	// 回到暂停menu
}

void Game::LoadArchive()
{
	std::vector<float> archive = Archive::load();
	if (archive.empty())
	{
		// load失败提示，然后回到mainmenu
	}

	float saveTime = archive[0];
	float saveHealth = archive[1];
	float saveScore = archive[2];
	int saveMonsterNum = archive[3];
	addTime = saveTime;
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	player->health = saveHealth;
	player->scores = saveScore;
	for (int i = 1; i <= saveMonsterNum; ++i)
		_monsterManager.NewMonster();
	// 跳到Playing
}

void Game::EmptyUpdate()
{
	_gameObjectManager.clock.restart();
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::View Game::view;
SplashScreen Game::_splashscreen;
Mainmenu Game::_mainmenu;
SettingScreen Game::_settingscreen;
PlayingLayer Game::_playinglayer;
PauseScreen Game::_pausescreen;
HelpScreen Game::_helpscreen;
sf::Clock Game::gameTime;
ObstacleManager Game::_obstacleManager;
AssetManager Game::_assetManager;
MonsterManager Game::_monsterManager;
BackGroundManager Game::_backgroundManager;
DieScreen Game::_diescreen;
sf::Music Game::_BGM_Mainmenu;
sf::Music Game::_BGM_Game;
float Game::addTime = 0;