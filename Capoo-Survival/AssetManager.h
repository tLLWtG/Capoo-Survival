#pragma once

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class AssetManager
{
public:
    AssetManager();

    static sf::Texture& GetTexture(std::string const& filename);
    static sf::Font& GetFont(std::string const& filename); // 新增的函数

private:
    std::map<std::string, sf::Texture> m_Textures;
    std::map<std::string, sf::Font> m_Fonts; // 新增的字体资源映射

    static AssetManager* sInstance;
};

#endif
