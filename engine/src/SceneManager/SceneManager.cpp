#include "SceneManager.hpp"

#include <iostream>

#include "../Game/Game.hpp"

SceneManager::SceneManager() {
    std::cout << "[SCENEMANAGER] se ejecuta el constructor" << std::endl;
    sceneLoader = std::make_unique<SceneLoader>();
}

SceneManager::~SceneManager(){
    sceneLoader.reset();
    std::cout << "[SCENEMANAGER] se ejecuta el destructor" << std::endl;
}

void SceneManager::loadSceneFromScript(const std::string& path, sol::state& lua) {
    // TODO verificar que el codigo sea correcto
    lua.script_file(path);
    sol::table scenes = lua["scenes"];

    int index = 0;
    while (true) {
        sol::optional<sol::table> hasScene = scenes[index];
        if (hasScene == sol::nullopt) {
            break;
        }
        sol::table scene = scenes[index];
        this->scenes.emplace(scene["name"], scene["path"]);

        if (index == 0) {
            nextScene = scene["name"];
        }

        index++;
    }
}

void SceneManager::loadScene() {
    Game& game = Game::getInstance();
    std::string scenePath = scenes[nextScene];
    sceneLoader->loadScene(scenePath, game.lua, game.assetManager, game.controllerManager
        , game.registry, game.renderer);
}

std::string SceneManager::getNextScene() const {
    return nextScene;
}

void SceneManager::setNextScene(const std::string& nextScene) {
    this->nextScene = nextScene;
}

bool SceneManager::IsSceneRunning() const{
    return isSceneRunning;
}

void SceneManager::startScene() {
    isSceneRunning = true;
}

void SceneManager::stopScene() {
    isSceneRunning = false;
}