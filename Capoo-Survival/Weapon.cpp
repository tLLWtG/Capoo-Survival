#include "stdafx.h"
#include "Weapon.h"
#include "PlayerChick.h"
#include "Game.h"
#include <cmath>

Weapon::Weapon() : weaponstate(Holding), m_Animator(GetSprite()) {

}

void Weapon::Update(float elapsedTime) {
	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	ChangeDirection(player->direction);
	GetSprite().setPosition(Game::view.getCenter());
	Fire();
	if (weaponstate == Attacking) {
		attackTime += elapsedTime;
		if (attackTime >= attackDuration)
			Hold();
	}
	m_Animator.Update(sf::seconds(elapsedTime));
}

void Weapon::Draw(sf::RenderWindow& window) {
	window.draw(GetSprite());
}
#define PI (3.1415926)
float getAngle(const sf::Vector2i& direction) {
	float angle = (std::atan2(direction.y, direction.x)) * 180.0f / PI;
	return angle;
}

void Weapon::ChangeDirection(sf::Vector2i direction) {
	float angle = getAngle(direction) + startAngle;
	if (!(0.0f <= angle < 360.0f)) {
		if (angle < 0)
			angle += 720.f;
		angle -= 360.0f * ((float)((int)((int)angle) / 360));
	}
	GetSprite().setRotation(angle);
}

void Weapon::Fire() {
	if (weaponstate == Holding) {
		weaponstate = Attacking;
		attackTime = 0.0f;
		m_Animator.SwitchAnimation("Attack");

		std::set<std::string>::iterator it = Game::GetMonsterManager().GetMonsterSet().begin();
		std::set<std::string>::iterator end = Game::GetMonsterManager().GetMonsterSet().end();
		/*
		for (; it != end; ++it) {
			std::string monsterName = *it;
			Monster* monsterPtr = Game::GetMonsterManager().GetMonsterSet().find(monsterName);

		}*/

	}
}

void Weapon::Hold() {
	if (weaponstate == Attacking) {
		weaponstate = Holding;
		m_Animator.SwitchAnimation("Hold");
	}
}

int min(int a, int b) {
	return a < b ? a : b;
}
int max(int a, int b) {
	return a > b ? a : b;
}
sf::IntRect getIntersectionInt(sf::FloatRect A, sf::FloatRect B) {
	int top = max((int)A.top, (int)B.top);
	int left = max((int)A.left, (int)B.left);
	int down = min((int)(A.top + A.height), (int)(B.top + B.height));
	int right = min((int)(A.left + A.width), (int)(B.left + B.width));
	return sf::IntRect(sf::Vector2i(left, top), sf::Vector2i(right - left, down - top));
}
bool Weapon::isHit(Monster& monster) {	// 还没测试不知道有没有bug
	sf::FloatRect weaponBounds = GetBoundingRect();
	sf::FloatRect monsterBounds = monster.GetBoundingRect();
	if (weaponBounds.intersects(monsterBounds) == false)
		return false;
	sf::Image weaponImage = GetSprite().getTexture()->copyToImage();
	sf::Image monsterImage = monster.GetTexture()->copyToImage();

	sf::IntRect intersection = getIntersectionInt(weaponBounds, monsterBounds);		
	for (int x = intersection.left; x <= intersection.left + intersection.width; x++)	
		for (int y = intersection.top; y <= intersection.top + intersection.height; y++) {
			sf::Color colorA = weaponImage.getPixel(x - GetSprite().getPosition().x, y - GetSprite().getPosition().y);	
			sf::Color colorB = monsterImage.getPixel(x - monster.GetPosition().x, y - monster.GetPosition().y);
			if (colorA.a > 0 && colorB.a > 0)
				return true;
		}
	return false;
}
