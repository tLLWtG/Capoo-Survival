#pragma once

class MonsterManager
{
public:

	MonsterManager();
	~MonsterManager();
	void Update();
	void NewMonster();
	void NewBoss();
	void Erase(std::string);
	int cnt;
	float lastUpdate;
	float lastWave;
	float lastBoss;
	std::set<std::string>& GetMonsterSet();

private:
	
	
	std::set<std::string>MonsterSet;
};