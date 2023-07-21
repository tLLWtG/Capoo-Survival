#include "stdafx.h"
#include "JumpText.h"
#include "AssetManager.h"

JumpText::JumpText(VisibleGameObject* master) : _master(master), _font(AssetManager::GetFont("Font/pixel.ttf")), remainder(0.0f) {
    _damegeText.setFont(_font);
    _damegeText.setCharacterSize(32);
    _damegeText.setStyle(sf::Text::Style::Bold);
    _damegeText.setOutlineThickness(0.5f);
}

void JumpText::SetDamage(int damage) {
    _damegeText.setString("-"+std::to_string(damage));
    _damegeText.setOrigin(_damegeText.getLocalBounds().width / 2, _damegeText.getLocalBounds().height / 2);
    _damegeText.setPosition(_master->GetBoundingRect().left + _master->GetBoundingRect().width / 2, _master->GetBoundingRect().top + 14);

    remainder = dieoutTime;
}

void JumpText::Update(float elapsedTime) {
    if (remainder > 0.0f) {
        SetAlpha(256.0f * remainder / dieoutTime);
        // 还没做跳跃效果
    //    SetAlpha(0.0f);
        remainder -= elapsedTime;
    }
}

void JumpText::Draw(sf::RenderWindow& window) {
    if (remainder > 0.0f)
        window.draw(_damegeText);
}

void JumpText::SetAlpha(float alpha) {
    _damegeText.setFillColor(sf::Color(220.0f, 20.0f, 60.0f, alpha));
    _damegeText.setOutlineColor(sf::Color(0.0f, 0.0f, 0.0f, alpha));
}