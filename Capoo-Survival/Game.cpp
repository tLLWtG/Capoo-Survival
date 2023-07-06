#include "Game.h"

Game::Game() : _window(sf::VideoMode(800, 600), "Capoo-Survival"), _player()
{

}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / frame_per_seconds);

	while (_window.isOpen())
	{
		processEvents();
		bool repaint = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			repaint = true;
			//update(TimePerFrame);
		}
		if (repaint)
			render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
		}
		else if (event.type == sf::Event::KeyReleased)
		{
		}
	}
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render()
{
	_window.clear();
	_window.draw(_player);
	_window.display();
}