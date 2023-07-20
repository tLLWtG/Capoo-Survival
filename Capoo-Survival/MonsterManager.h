#pragma once

class MonsterManager
{
public:

	MonsterManager();
	~MonsterManager();
	void Update();
	void Erase(std::string);
	int cnt;
	float lastUpdate;
	std::set<std::string>& GetMonsterSet();

private:
	
	
	std::set<std::string>MonsterSet;
};