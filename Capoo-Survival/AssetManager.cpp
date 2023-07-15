#include "AssetManager.h"
#include <assert.h>

AssetManager assetmanager;

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
    auto& MusicMap = sInstance->m_Musics;

    auto pairFound = MusicMap.find(filename);
    if (pairFound != MusicMap.end()) {
        return pairFound->second;
    }

    auto& music = MusicMap[filename];
    music.openFromFile(filename);
    return music;
}

sf::Font& AssetManager::GetFont(std::string const& filename) {
    auto& FontMap = sInstance->m_Fonts;

    auto pairFound = FontMap.find(filename);
    if (pairFound != FontMap.end()) {
        return pairFound->second;
    }

    auto& font = FontMap[filename];
    font.loadFromFile(filename);
    return font;
}


sf::Texture& AssetManager::GetTexture(std::string const& filename) {
    auto& TextureMap = sInstance->m_Textures;

    auto pairFound = TextureMap.find(filename);
    if (pairFound != TextureMap.end()) {
        return pairFound->second;
    }

    auto& texture = TextureMap[filename];
    texture.loadFromFile(filename);
    return texture;
}