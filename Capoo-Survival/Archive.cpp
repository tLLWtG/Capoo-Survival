#include "stdafx.h"
#include "Archive.h"
#include "Game.h"
#include "PlayerChick.h"
#include "MonsterManager.h"

bool Archive::save()
{
	std::ofstream out_file(fileName, std::ios::out);
	if (!out_file)
	{
		return false;
	}
	Json::Value root;
	Json::FastWriter fastWriter;

	float saveTime = Game::gameTime.getElapsedTime().asSeconds();
	saveTime += Game::addTime;

	PlayerChick* player = dynamic_cast<PlayerChick*>(Game::GetGameObjectManager().Get("player"));
	float saveHealth = player->health;
	float saveScore = player->scores;
	
	int saveMonsterNum = Game::GetMonsterManager().GetMonsterSet().size();

	root["Time"] = Json::Value(saveTime);
	root["Health"] = Json::Value(saveScore);
	root["Score"] = Json::Value(saveScore);
	root["MonsterNum"] = Json::Value(saveMonsterNum);

	out_file << fastWriter.write(root);
	out_file.close();
	return true;
}

std::vector<float> Archive::load()
{
	std::ifstream in_file(fileName, std::ios::in);
	if (!in_file)
	{
		std::vector<float> temp;
		return temp;
	}

	std::string jsonContent;
	Json::Value root;
	Json::Reader reader;

	in_file >> jsonContent;
	in_file.close();
	reader.parse(jsonContent, root);

	float saveTime = root["Time"].asFloat();
	float saveHealth = root["Health"].asFloat();
	float saveScore = root["Score"].asFloat();
	int saveMonsterNum = root["MonsterNum"].asInt();

	

	std::vector<float> res;
	res.push_back(saveTime);
	res.push_back(saveHealth);
	res.push_back(saveScore);
	res.push_back(saveMonsterNum);

	return res;
}

const std::string Archive::fileName = "archive.json";