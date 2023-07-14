#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
    assert(sInstance == nullptr);
    sInstance = this;
}

AssetManager::~AssetManager()
{
    sInstance = nullptr;
}

sf::Music& AssetManager::GetMusic(std::string const& filename) {
    auto& MusMap = sInstance->m_Musics;

    auto pairFound = MusMap.find(filename);
    if (pairFound != MusMap.end()) {
        return pairFound->second;
    }

    auto& music = MusMap[filename];
    music.openFromFile(filename);
    return music;
}

sf::Font& AssetManager::GetFont(std::string const& filename) {
    auto& FonMap = sInstance->m_Fonts;

    auto pairFound = FonMap.find(filename);
    if (pairFound != FonMap.end()) {
        return pairFound->second;
    }

    auto& font = FonMap[filename];
    font.loadFromFile(filename);
    return font;
}


sf::Texture& AssetManager::GetTexture(std::string const& filename) {
    auto& texMap = sInstance->m_Textures;

    auto pairFound = texMap.find(filename);
    if (pairFound != texMap.end()) {
        return pairFound->second;
    }

    auto& texture = texMap[filename];
    texture.loadFromFile(filename);
    return texture;
}