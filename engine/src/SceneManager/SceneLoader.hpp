#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

class SceneLoader {
  private:
    void loadSprites(SDL_Renderer* renderer, const sol::table& sprites
        , std::unique_ptr<AssetManager>& assetManager);
    void loadFonts(const sol::table& fonts
        , std::unique_ptr<AssetManager>& assetManager);
    void loadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);
    void loadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);
    void loadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);

  public: 
    SceneLoader();
    ~SceneLoader();
    void loadScene(const std::string& scenePath, sol::state& lua
        , std::unique_ptr<AssetManager>& assetManager
        , std::unique_ptr<ControllerManager>& controllerManager
        , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};


#endif // SCENELOADER_HPP