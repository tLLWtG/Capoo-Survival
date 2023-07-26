#include "stdafx.h"
#include "Interface.h"
#include "HelpScreen.h"
#include "Animator.h"
#include "Game.h"


HelpScreen::HelpScreen() :_title_texture(AssetManager::GetTexture("Image/Screen/help_title.png")),_help_font(AssetManager::GetFont("Font/Fixedsys62.ttf")) {
	_text_title.setTexture(_title_texture);
	_text_title.setScale(1.0f, 1.2f);
	_text_title.setOrigin(_text_title.getLocalBounds().width / 2, _text_title.getLocalBounds().height / 2);

	sf::Texture& texture = AssetManager::GetTexture("Image/Mainmenu/Frame.png");
	_frame_sprite.setTexture(texture);
	_frame_sprite.setOrigin(_frame_sprite.getLocalBounds().width / 2, _frame_sprite.getLocalBounds().height / 2);
	_frame_sprite.setScale(1.24f, 1.24f);

	sf::Text temp;
	temp.setFont(_help_font);
	temp.setCharacterSize(30);
	temp.setFillColor(sf::Color(165, 42, 42));

	temp.setString(L"[esc] 	Return or Pause");
	_paragraph.push_back(temp);

	temp.setString(L"[Up] 	 Move Up");
	_paragraph.push_back(temp);
	
	temp.setString(L"[Down]    Move Down");
	_paragraph.push_back(temp);

	temp.setString(L"[Left]    Move Left");
	_paragraph.push_back(temp);

	temp.setString(L"[Right]   Move Right");
	_paragraph.push_back(temp);

	temp.setString(L"[S] 	  Release Skills!");
	_paragraph.push_back(temp);
}

bool HelpScreen::show(sf::RenderWindow& window) {
	static sf::Sprite background_sprite;
	background_sprite.setPosition(0 + getWindowStart().x, 300.0f + getWindowStart().y);
	Animator animator(background_sprite);
	auto& cloudAnimation = animator.CreateAnimation("clouds", "Image/Mainmenu/cloud_1285x61.png", sf::seconds(2), true);
	cloudAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(1285, 61), 30);

	setBackground("Image/Mainmenu/background_glass.png");

	
	sf::Clock clock;
	sf::Event event;
	while (window.pollEvent(event));
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				return 0;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				return 1;
		}
		window.clear();
		animator.Update(clock.restart());
		drawBackground(window);
		window.draw(background_sprite);
		
		draw_title(window);
		draw_frame(window);

		float h = Game::view.getCenter().y - 90;
		for (int i = 0; i < _paragraph.size(); i++) {
			_paragraph[i].setPosition(Game::view.getCenter().x - 190, h);
			h += 50;
			window.draw(_paragraph[i]);
		}

		drawMouse(window);
		window.display();
	}

	
}


void HelpScreen::draw_title(sf::RenderWindow& window) {
	_text_title.setPosition(Game::view.getCenter().x, Game::view.getCenter().y - 250);
	window.draw(_text_title);
}
void HelpScreen::draw_frame(sf::RenderWindow& window) {
	_frame_sprite.setPosition(Game::view.getCenter().x, Game::view.getCenter().y + 75);
	window.draw(_frame_sprite);
}