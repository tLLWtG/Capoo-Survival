#include "stdafx.h"
#include "Animator.h"
#include "AssetManager.h"


Animator::Animator(sf::Sprite& sprite) :m_Sprite(sprite), m_CurrentTime(), m_CurrentAnimation(nullptr) {}
Animator::~Animator() {}

Animator::Animation& Animator::CreateAnimation(std::string const& name, std::string const textureName, sf::Time const& duration, bool loop)
{
	m_Animations.push_back(Animator::Animation(name, textureName, duration, loop));

	if (m_CurrentAnimation == nullptr)
		SwitchAnimation(&m_Animations.back());

	return m_Animations.back();
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{
	if (animation != nullptr)
	{
		m_Sprite.setTexture(AssetManager::GetTexture(animation->m_TextureName));
	}

	m_CurrentAnimation = animation;

	m_CurrentTime = sf::Time::Zero;
}

Animator::Animation* Animator::FindAnimation(std::string const& name)
{
	for (auto it = m_Animations.begin(); it != m_Animations.end(); it++)
	{
		if (it->m_Name == name)
			return &*it;
	}
	return nullptr;
}

bool Animator::SwitchAnimation(std::string const& name)
{
	auto animation = FindAnimation(name);
	if (animation != nullptr)
	{
		SwitchAnimation(animation);
		return true;
	}

	return false;
}

std::string Animator::GetCurrentAnimationName()const
{

	if (m_CurrentAnimation != nullptr)
		return m_CurrentAnimation->m_Name;
	return "";
}

void Animator::Update(sf::Time const& dt)
{

	if (m_CurrentAnimation == nullptr)
		return;

	m_CurrentTime += dt;

	float scaledTime = m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds();
	int numsFrames = m_CurrentAnimation->m_Frames.size();
	int currentFrame = static_cast<int>(scaledTime * numsFrames);

	if (m_CurrentAnimation->m_looping)
	{
		currentFrame %= numsFrames;
	}
	else if (currentFrame >= numsFrames)
	{
		currentFrame = numsFrames - 1;
	}

	m_Sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]);
}
