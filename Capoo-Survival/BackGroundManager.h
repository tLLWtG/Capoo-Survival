#pragma once

#include "BackGround.h"
#include "VisibleGameObject.h"


class BackGroundManager
{
public:

	BackGroundManager();
	~BackGroundManager();

	std::set<std::string>&GetBackGroundSet();
private:
	std::set<std::string>BackGroundSet;
};