#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <sol/sol.hpp>

#include <memory>

#include "../ControllerManager/ControllerManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneLoader.hpp"
#include "../SceneManager/SceneManager.hpp"

const int FPS = 30;
const int MILLISEC_PER_FRAME = 1000 / FPS;

class Game {
  private:
    SDL_Window* window = nullptr;
    bool isRunning = false;
    int windowWidth = 0;
    int windowHeight = 0;
    int millisecsPreviousFrame = 0;
    Mix_Chunk* gunshotSound;
    
  public:    
    SDL_Renderer* renderer = nullptr;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<ControllerManager> controllerManager;
    std::unique_ptr<SceneManager> sceneManager;
    sol::state lua;
    int aliveZombies = 0;

  private:
    void setup();
    void runScene();
    void processInput();
    void update();
    void render();    
    Game();
    ~Game();   
    
  public:
    static Game& getInstance();
    void init();
    void run();
    void playGunshotSound();
    void destroy();
};

#endif // GAME_HPP