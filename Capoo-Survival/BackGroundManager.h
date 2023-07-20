#pragma once

#include "BackGround.h"
#include "VisibleGameObject.h"


class BackGroundManager
{
public:

	BackGroundManager();
	~BackGroundManager();
	void Update();
private:
	static int cnt;
};