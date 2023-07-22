#pragma once

class Archive
{
public:
	static bool save();
	static std::vector<float> load();

private:
	const static std::string fileName;
};