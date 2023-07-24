#include "stdafx.h"
#include "Skill_Spurt.h"
#include "Animator.h"
#include "Game.h"

Skill_Spurt::Skill_Spurt() {
    auto& fireAnimation = m_Animator.CreateAnimation("Attack", "Image/Skill/skill_spurt_94x205.png", sf::seconds(1), true);
    fireAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(94, 205), 60);
    GetSprite().setOrigin(sf::Vector2f(47.0f, 23.0f));
    startAngle = -90;
    attackDuration = 1.0f;
    cdTime = 2.0f;

    attackPower = 20.0f;
    GetSprite().setScale(3.0f, 3.0f);
}

Skill_Spurt::~Skill_Spurt() {

}

void Skill_Spurt::Update(float elapsedTime) {
    static const float damage_interval = 0.3f;
    static float last_damage_time = 0.0f;
    if (skillstate == Attacking) {
        last_damage_time += elapsedTime;
        if (last_damage_time >= damage_interval) {
            last_damage_time = 0.0f;
            std::set<std::string>& obs = Game::GetMonsterManager().GetMonsterSet();
            GameObjectManager& gameObjectManager = Game::GetGameObjectManager();

            for (auto& x : obs) {
                Monster* monsterPtr = dynamic_cast<Monster*>(gameObjectManager.Get(x));
                if (monsterPtr != nullptr && isHit(monsterPtr)) {
                    monsterPtr->getDamage(attackPower);
                }
            }
        }
    }
    Skill::Update(elapsedTime);
}