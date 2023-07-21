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

		std::set<std::string>& obs = Game::GetMonsterManager().GetMonsterSet();
		GameObjectManager& gameObjectManager = Game::GetGameObjectManager();

		for (auto& x : obs) {
			Monster* monsterPtr = dynamic_cast<Monster*>(gameObjectManager.Get(x));
			if (monsterPtr != nullptr && isHit(monsterPtr)) {
				monsterPtr->getDamage(attackPower);

				weaponstate = Attacking;
				attackTime = 0.0f;
				m_Animator.SwitchAnimation("Attack");
			//	GetSprite().setScale(1.2f, 1.2f);
			}
		}

	}
}



void Weapon::Hold() {
	if (weaponstate == Attacking) {
		weaponstate = Holding;
		m_Animator.SwitchAnimation("Hold");
	//	GetSprite().setScale(1.0f, 1.0f);
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

bool Weapon::isHit(const Monster* monsterPtr) {
	if (!monsterPtr)
		return false;
	sf::FloatRect weaponBounds = GetBoundingRect();
	sf::FloatRect monsterBounds = monsterPtr->GetBoundingRect();
	return weaponBounds.intersects(monsterBounds);
}

void Weapon::setHandle() {
	GetSprite().setOrigin(0, 0);
}

void Weapon::resetHandle() {
	GetSprite().setOrigin(0, 0);
}

void Weapon::setSize(float multiple) {
	GetSprite().setScale(multiple, multiple);
}