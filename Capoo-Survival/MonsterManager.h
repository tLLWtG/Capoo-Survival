#pragma once

class MonsterManager
{
public:

	MonsterManager();
	~MonsterManager();
	void Update();
	void Erase(std::string);
	std::set<std::string>& GetMonsterSet();

private:
	int cnt;
	float lastUpdate;
	std::set<std::string>MonsterSet;
};