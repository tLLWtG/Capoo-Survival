#include "stdafx.h"
#include "JumpText.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Game.h"

JumpText::JumpText(VisibleGameObject* master) : _master(master), _font(AssetManager::GetFont("Font/pixel.ttf")), remainder(0.0f), isDamage(true),m_healingAnimator(_healing) {
    _damegeText.setFont(_font);
    _damegeText.setCharacterSize(50);
    _damegeText.setStyle(sf::Text::Style::Bold);
    _damegeText.setOutlineThickness(1.2f);

    auto& healAnimation = m_healingAnimator.CreateAnimation("Healing", "Image/Animator/healing_135x145.png", sf::seconds(0.66f), true);
    healAnimation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(135, 145), 40);
    _healing.setOrigin(_healing.getLocalBounds().width / 2, _healing.getLocalBounds().height / 2);
    _healing.setScale(10.0f, 10.0f);
  
}

void JumpText::SetDamage(int damage) {
    if (damage == 0)
        return;
    isDamage = damage>0;

    if (isDamage) 
        _damegeText.setString("-" + std::to_string(damage));
    else
        _damegeText.setString("+" + std::to_string(-damage));

    _damegeText.setOrigin(_damegeText.getLocalBounds().width / 2, _damegeText.getLocalBounds().height / 2);
    _damegeText.setPosition(_master->GetBoundingRect().left + _master->GetBoundingRect().width / 2, _master->GetBoundingRect().top + 34);

    remainder = dieoutTime;
}

void JumpText::Update(float elapsedTime) {
    if (remainder > 0.0f) {
        SetAlpha(256.0f * remainder / dieoutTime);
        // 还没做跳跃效果
        remainder -= elapsedTime;
        if (isDamage == false) {
            //_healing.setPosition(_master->GetPosition());
            _healing.setPosition(Game::view.getCenter());
            m_healingAnimator.Update(sf::seconds(elapsedTime));
        }
    }
}

void JumpText::Draw(sf::RenderWindow& window) {
    if (remainder > 0.0f) {
        window.draw(_damegeText);
        if (isDamage == false)
            window.draw(_healing);
    }
}

void JumpText::SetAlpha(float alpha) {
    if (isDamage) {
        _damegeText.setFillColor(sf::Color(220.0f, 20.0f, 60.0f, alpha));
        _damegeText.setOutlineColor(sf::Color(0.0f, 0.0f, 0.0f, alpha));
    }
    else {
        _damegeText.setFillColor(sf::Color(0.0f, 205.0f, 0.0f, alpha));
        _damegeText.setOutlineColor(sf::Color(0.0f, 0.0f, 0.0f, alpha));
    }
}