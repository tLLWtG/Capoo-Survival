#pragma once

class Archive
{
public:
	static void save();
	static void load();

private:
	const static std::string fileName;
};