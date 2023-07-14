#pragma once
#pragma once

#include "stdafx.h"

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    static sf::Font& GetFont(std::string const& filename);
    static sf::Music& GetMusic(std::string const& filename);
    static sf::Texture& GetTexture(std::string const& filename);

private:

    std::map<std::string, sf::Font> m_Fonts;
    std::map<std::string, sf::Music> m_Musics;
    std::map<std::string, sf::Texture> m_Textures;

    static AssetManager* sInstance;
};

