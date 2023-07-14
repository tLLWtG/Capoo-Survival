#pragma once

class Archive
{
public:
	static bool save();
	static bool load();

private:
	const static std::string fileName;
};