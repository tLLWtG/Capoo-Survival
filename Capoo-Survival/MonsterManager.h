#pragma once

class MonsterManager
{
public:

	MonsterManager();
	~MonsterManager();
	static void Update();
	//static void erase();
	//static std::set<std::string>& GetMonsterSet();
private:
	static char cnt;
	static std::set<std::string>MonsterSet;
};