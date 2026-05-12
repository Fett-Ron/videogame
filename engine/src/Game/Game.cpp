#include <iostream>

#include "Game.hpp"

#include "../Components/AnimationComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"

#include "../Events/ClickEvent.hpp"

#include "../Systems/AnimationSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/UISystem.hpp"

Game::Game() : isRunning(false) {
    std::cout << "[GAME] Se ejecuta constructor" << std::endl;
    assetManager = std::make_unique<AssetManager>();
    eventManager = std::make_unique<EventManager>();
    registry = std::make_unique<Registry>();
    controllerManager = std::make_unique<ControllerManager>();
    sceneManager = std::make_unique<SceneManager>();
    
}

Game::~Game() {
    assetManager.reset();
    registry.reset();
    eventManager.reset();
    controllerManager.reset();
    sceneManager.reset();
    std::cout << "[GAME] Se ejecuta destructor" << std::endl;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "[GAME] Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if(TTF_Init() != 0) {
        std::cerr << "[GAME] Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "[GAME] Error al instatic_cast<int>(transform.position.x)icializar SDL_image: " << IMG_GetError() << std::endl;
        return;
    }

    windowWidth = 800;
    windowHeight = 600;
    window = SDL_CreateWindow(
        "Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    if(!window) {
        std::cerr << "[GAME] Error al crear la ventana: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        std::cerr << "[GAME] Error al crear el renderizador: " << SDL_GetError() << std::endl;
        return;
    }

    isRunning = true;
}

void Game::setup() {
    registry->addSystem<RenderSystem>();
    registry->addSystem<ScriptSystem>();
    registry->addSystem<MovementSystem>();
    registry->addSystem<CollisionSystem>();    
    registry->addSystem<DamageSystem>();
    registry->addSystem<AnimationSystem>();
    registry->addSystem<RenderTextSystem>();
    registry->addSystem<UISystem>();

    sceneManager->loadSceneFromScript("./assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math);
    lua.script_file("./assets/scripts/player.lua");
    lua.script_file("./assets/scripts/zombie.lua");
    registry->getSystem<ScriptSystem>().createLuaBinding(lua);    
}

void Game::processInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    sceneManager->stopScene();
                    isRunning = false;
                }
                controllerManager->keyDown(sdlEvent.key.keysym.sym);
                break;
            case SDL_KEYUP:
                controllerManager->keyUp(sdlEvent.key.keysym.sym);
                break;
            case SDL_MOUSEMOTION:
                int x, y;
                SDL_GetMouseState(&x,&y);
                controllerManager->setMousePosition(x,y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                controllerManager->setMousePosition(sdlEvent.button.x, sdlEvent.button.y);
                controllerManager->mouseButtonDown(static_cast<int>(sdlEvent.button.button));                
                eventManager->emitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button)
                    , sdlEvent.button.x, sdlEvent.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                controllerManager->setMousePosition(sdlEvent.button.x, sdlEvent.button.y);
                controllerManager->mouseButtonUp(static_cast<int>(sdlEvent.button.button));                
                break;
            default:
                break;
        }
        
    }
}

void Game::update() {
    int timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (0 < timeToWait && timeToWait <= MILLISEC_PER_FRAME) {
        SDL_Delay(timeToWait);
    }
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    // TODO: agregar esta variable al estado de LUA

    millisecsPreviousFrame = SDL_GetTicks();
    
    // reiniciar las subscripciones
    eventManager->reset();
    registry->getSystem<DamageSystem>().subscribeToCollisionEvent(eventManager);
    registry->getSystem<UISystem>().SubscribeToClickEvent(eventManager);

    registry->update();

    registry->getSystem<ScriptSystem>().update(lua);

    registry->getSystem<AnimationSystem>().update();
    registry->getSystem<MovementSystem>().update(deltaTime);
    registry->getSystem<CollisionSystem>().update(eventManager);    
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
    SDL_RenderClear(renderer);  
    registry->getSystem<RenderSystem>().Update(renderer, assetManager);
    registry->getSystem<RenderTextSystem>().update(renderer, assetManager);
    SDL_RenderPresent(renderer);
}

void Game::runScene() {
    sceneManager->loadScene();

    while (sceneManager->IsSceneRunning()) {
        processInput();
        update();
        render();
    }
    
    assetManager->clearAssets();
    registry->clearAllEntities(); 
}

void Game::run() {
    setup();
    while(isRunning) {
        sceneManager->startScene();
        runScene();
    }
}

void Game::destroy() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if(window) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit(); 
}