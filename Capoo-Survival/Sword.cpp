#include "stdafx.h"
#include "Sword.h"


Sword::Sword() : Weapon() {
    attackPower = 30;
    attackDuration = 0.5f;

    GetSprite().setOrigin(0, 17);
    _special_sprite.setOrigin(-7, 60);
    setSize(2.0f);

    auto& holdAnimation = m_Animator.CreateAnimation("Hold", "Image/Weapon/sword_hold_90x33.png", sf::seconds(1), true);
    holdAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(90, 33), 60);

    auto& holdSpecialAnimation = m_special.CreateAnimation("Hold_special", "Image/Weapon/sword_hold_special_109x107.png", sf::seconds(1), true);
    holdSpecialAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(109, 107), 60);

    auto& attackAnimation = m_Animator.CreateAnimation("Attack", "Image/Weapon/sword_attack_160x160.png", sf::seconds(0.5), true);
    attackAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(160, 160), 30);
    m_Animator.SwitchAnimation("Hold");
}

void Sword::Update(float elapsedTime) {
    if (weaponstate == Holding) {
        GetSprite().setOrigin(0, 17);
        _special_sprite.setOrigin(-7, 60);
    }
    else {
        GetSprite().setOrigin(13, 89);
    }
    Weapon::Update(elapsedTime);
}