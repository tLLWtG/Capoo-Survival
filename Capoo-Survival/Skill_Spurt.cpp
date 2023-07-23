#include "stdafx.h"
#include "Skill_Spurt.h"
#include "Animator.h"

Skill_Spurt::Skill_Spurt() {
    auto& fireAnimation = m_Animator.CreateAnimation("Attack", "Image/Skill/skill_spurt_94x205.png", sf::seconds(1), true);
    fireAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(94, 205), 60);
    GetSprite().setOrigin(sf::Vector2f(47.0f, 23.0f));
    startAngle = -90;
    attackDuration = 1.0f;
}

Skill_Spurt::~Skill_Spurt() {

}