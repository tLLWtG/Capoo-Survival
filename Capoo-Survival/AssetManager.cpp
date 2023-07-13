#include "AssetManager.h"
#include <assert.h>

AssetManager assetmanager;

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
    assert(sInstance == nullptr);
    sInstance = this;
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

sf::Font& AssetManager::GetFont(std::string const& filename) {
    auto& fontMap = sInstance->m_Fonts;

    auto pairFound = fontMap.find(filename);
    if (pairFound != fontMap.end()) {
        return pairFound->second;
    }

    auto& font = fontMap[filename];
    font.loadFromFile(filename);
    return font;
}
