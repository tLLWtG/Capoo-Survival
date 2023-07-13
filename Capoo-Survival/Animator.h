#pragma once
#pragma once
#include "stdafx.h"

class Animator
{
public:
	struct Animation
	{
		std::string m_Name;
		std::string m_TextureName;
		std::vector<sf::IntRect>m_Frames;// 帧列表
		sf::Time m_Duration;// 周期时间
		bool m_looping;

		Animation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool looping) :
			m_Name(name), m_TextureName(textureName), m_Duration(duration), m_looping(looping) {}

		void AddFrames(sf::Vector2i const& startFrom, sf::Vector2i const& frameSize, unsigned int frames)
		{
			sf::Vector2i current = startFrom;
			for (unsigned int i = 0; i < frames; i++)
			{
				m_Frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
				current.x += frameSize.x;
			}
		}
	};

	Animator(sf::Sprite& sprite);
	~Animator();
	virtual Animator::Animation& CreateAnimation(std::string const& name, std::string const textureName, sf::Time const& duration, bool loop = true);// 默认循环
	virtual bool SwitchAnimation(std::string const& name);
	virtual std::string GetCurrentAnimationName()const;

	// void update(sf::Time const& dt);// 在派生类中实现
private:
	virtual Animator::Animation* FindAnimation(std::string const& name);
	virtual void SwitchAnimation(Animator::Animation* animation);

	sf::Sprite& m_Sprite;
	sf::Time m_CurrentTime;
	std::list<Animator::Animation>m_Animations;
	Animator::Animation* m_CurrentAnimation;
};