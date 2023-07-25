#include "stdafx.h"
#include "Interface.h"
#include "SettingScreen.h"
#include "AssetManager.h"
#include "Game.h"

#include "Mainmenu.h"
#include "PlayerChick.h"

SettingScreen::SettingScreen() :_title_texture(AssetManager::GetTexture("Image/Screen/setting_title.png")), _music(250.0f, 15.0f, 100.0f, 100.0f), _volume(250.0f, 15.0f, 100.0f, 100.0f),
_music_icon(AssetManager::GetTexture("Image/IconButton/music.png")), _volume_icon(AssetManager::GetTexture("Image/IconButton/volume.png")) {
	_text_title.setTexture(_title_texture);
	_text_title.setScale(1.0f, 1.2f);
	_text_title.setOrigin(_text_title.getLocalBounds().width / 2, _text_title.getLocalBounds().height / 2);

	sf::Texture& texture = AssetManager::GetTexture("Image/Mainmenu/Frame.png");
	_frame_sprite.setTexture(texture);
	_frame_sprite.setOrigin(_frame_sprite.getLocalBounds().width / 2, _frame_sprite.getLocalBounds().height / 2);
	_frame_sprite.setScale(1.24f, 1.24f);

	_music_icon.setScale(0.8f, 0.8f);
	_music_icon.setOrigin(_music_icon.getLocalBounds().width / 2, _music_icon.getLocalBounds().height / 2);
	_volume_icon.setScale(0.8f, 0.8f);
	_volume_icon.setOrigin(_volume_icon.getLocalBounds().width / 2, _volume_icon.getLocalBounds().height / 2);
}

int SettingScreen::show(sf::RenderWindow& window, int _from) {
	static sf::Sprite background_sprite;
	background_sprite.setPosition(0 + getWindowStart().x, 300.0f + getWindowStart().y);
	Animator animator(background_sprite);
	auto& cloudAnimation = animator.CreateAnimation("clouds", "Image/Mainmenu/cloud_1285x61.png", sf::seconds(2), true);
	cloudAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(1285, 61), 30);
	sf::Clock clock;

	_music.setValue(100.0f, getMusic());
	_volume.setValue(100.0f, getVolume());

	while (window.isOpen()) {
		while (window.pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				return 0;
			else if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) {
				detectPressMouse(window);
			}
			else if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left) {
				_music.state = false;
				_volume.state = false;
			}
			else if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
				return 1;
		}
		window.clear();
		static bool uninitialized = true;
		switch (_from)
		{
		case 0: {
			animator.Update(clock.restart());
			if (uninitialized) {
				setBackground("Image/Mainmenu/background_glass.png");
				uninitialized = false;
			}
			drawBackground(window);
			window.draw(background_sprite);
		}
		case 1: {
			window.clear(sf::Color(52, 103, 49));
			Game::GetGameObjectManager().DrawAll(window);
			darkenWindow(window);
		}
		default:
			break;
		}
		draw_title(window);
		draw_frame(window);

		if (_music.state) {
			_music.follow(window);
			setMusic(_music.getValue());
		}
		_music_icon.setPosition(Game::view.getCenter().x - 150, Game::view.getCenter().y - 50);
		window.draw(_music_icon);
		_music.setPosition(Game::view.getCenter().x + 40, Game::view.getCenter().y - 50);
		_music.draw(window);

		if (_volume.state) {
			_volume.follow(window);
			setVolume(_volume.getValue());
		}
		_volume_icon.setPosition(Game::view.getCenter().x - 150, Game::view.getCenter().y + 30);
		window.draw(_volume_icon);
		_volume.setPosition(Game::view.getCenter().x + 40, Game::view.getCenter().y + 30);
		_volume.draw(window);

		drawMouse(window);
		
		
		window.display();
	}

}

void SettingScreen::draw_title(sf::RenderWindow& window) {
	_text_title.setPosition(Game::view.getCenter().x, Game::view.getCenter().y - 250);
	window.draw(_text_title);
}
void SettingScreen::draw_frame(sf::RenderWindow& window) {
	_frame_sprite.setPosition(Game::view.getCenter().x, Game::view.getCenter().y + 75);
	window.draw(_frame_sprite);
}

void SettingScreen::detectPressMouse(sf::RenderWindow& window) {
	sf::Vector2i mousePosition = getMousePosition(window);
	if (_music.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
		_music.state = true;
	else if (_volume.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
		_volume.state = true;
}

void SettingScreen::setMusic(float value) {
	Game::_BGM_Game.setVolume(value);
	Game::_BGM_Mainmenu.setVolume(value);
}

void SettingScreen::setVolume(float value) {
	PlayerChick::voice_hurt.setVolume(value);

}

float SettingScreen::getMusic() {
	return Game::_BGM_Game.getVolume();
}

float SettingScreen::getVolume() {
	return PlayerChick::voice_hurt.getVolume();
}

/*

f (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (slider.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
						// 如果鼠标点击在滑动条上，则允许拖动
						sf::Vector2f sliderPosition = slider.getPosition();
						float yOffset = mousePosition.y - static_cast<int>(sliderPosition.y);
						while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							mousePosition = sf::Mouse::getPosition(window);
							float newY = static_cast<float>(mousePosition.y) - yOffset;
							if (newY < 200.f) {
								newY = 200.f;
							} else if (newY > 400.f) {
								newY = 400.f;
							}
							slider.setPosition(sliderPosition.x, newY);
							// 根据滑动条位置更新音量
							float volumeLevel = 100.f - ((newY - 200.f) / sliderMaxHeight) * 100.f;
							music.setVolume(volumeLevel);
							window.clear();
							window.draw(slider);
							window.display();
						}
					}
				}
			}
*/