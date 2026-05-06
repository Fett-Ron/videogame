#include "AssetManager.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

AssetManager::AssetManager(){
    std::cout << "[AssetManager] Se ejecuta el constructor" << std::endl;
}

AssetManager::~AssetManager(){
    std::cout << "[AssetManager] Se ejecuta el destructor" << std::endl;
}

void AssetManager::clearAssets(){
    for (auto texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto font : fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();
}

void AssetManager::addTexture(SDL_Renderer* renderer, const std::string& textureId
    , const std::string& filePath){
    
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "[AssetManager] Error al cargar imagen " << filePath << ": " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "[AssetManager] Error al crear textura para " << filePath << ": " << SDL_GetError() << std::endl;
        return;
    }

    textures.emplace(textureId, texture);
}

SDL_Texture* AssetManager::getTexture(const std::string& textureId){
    return textures[textureId];
}

void AssetManager::addFont(const std::string& fontId, const std::string& filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (font == NULL) {
        std::string error = TTF_GetError();
        std::cout << "[ASSETMANAGER] " << error << std::endl;
        return;
    }
    fonts.emplace(fontId, font);
}

TTF_Font* AssetManager::getFont(const std::string& fontId) {
    return fonts[fontId];
}