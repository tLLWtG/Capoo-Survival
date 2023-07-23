#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Skill.h"
#include "PlayerChick.h"
#include "Game.h"

Skill::Skill() :skillstate(Waiting), remainingWaitingTime(0.0f), m_Animator(GetSprite()) {

}

void Skill::Update(float elapsedTime) {
	if (skillstate == Attacking) {
		m_Animator.Update(sf::seconds(elapsedTime));
		attackTime += elapsedTime;
		if (attackTime >= attackDuration)
			Wait();
	}
	else {
		if (remainingWaitingTime > 0.0f)
			remainingWaitingTime -= elapsedTime;
	}
}


void Skill::Fire() {
	if (skillstate == Waiting && remainingWaitingTime <= 0.0f) {	// ת��Ϊ����ģʽ
		PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
		ChangeDirection(player->direction);
		GetSprite().setPosition(Game::view.getCenter());

		skillstate = Attacking;
		attackTime = 0.0f;

		// ��û�������ж�
		/*
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
		}*/

	}
}

void Skill::Wait() {
	if (skillstate == Attacking) {
		skillstate = Waiting;
		m_Animator.SwitchAnimation("Hold");
		remainingWaitingTime = cdTime;
	}
}

void Skill::Draw(sf::RenderWindow& window) {
	if (skillstate == Attacking)
		window.draw(GetSprite());
}
#define PI (3.1415926)
inline float getAngle(const sf::Vector2i& direction) {
	float angle = (std::atan2(direction.y, direction.x)) * 180.0f / PI;
	return angle;
}
void Skill::ChangeDirection(sf::Vector2i direction) {
	float angle = getAngle(direction) + startAngle;
	if (!(0.0f <= angle < 360.0f)) {
		if (angle < 0)
			angle += 720.f;
		angle -= 360.0f * ((float)((int)((int)angle) / 360));
	}
	GetSprite().setRotation(angle);
}

bool Skill::isHit(const Monster* monsterPtr) { /*
	if (!monsterPtr)
		return false;
	sf::FloatRect weaponBounds = GetBoundingRect();
	sf::FloatRect monsterBounds = monsterPtr->GetBoundingRect();
	return weaponBounds.intersects(monsterBounds);*/
}