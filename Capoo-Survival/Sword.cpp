#include "stdafx.h"
#include "Sword.h"


Sword::Sword() : Weapon() {
    attackPower = 30;
    attackDuration = 0.5f;

    GetSprite().setOrigin(13, 89);
    startAngle = 37;

    auto& holdAnimation = m_Animator.CreateAnimation("Hold", "Image/Weapon/sword_hold_160x160.png", sf::seconds(0.5), true);
    holdAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(160, 160), 30);
    auto& attackAnimation = m_Animator.CreateAnimation("Attack", "Image/Weapon/sword_attack_160x160.png", sf::seconds(0.5), true);
    attackAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(160, 160), 30);
    m_Animator.SwitchAnimation("Hold");
}