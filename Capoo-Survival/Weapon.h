#pragma once
#include "VisibleGameObject.h"
#include "Animation.h"

class Weapon :public VisibleGameObject {
public:
	Weapon();

	Animator m_animator;
	
	void Load(std::string filename) {
		_texture = AssetManager::GetTexture(filename);
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}

	void Draw(sf::RenderWindow& window) override {

	}
	void Fire() {

	}



};
