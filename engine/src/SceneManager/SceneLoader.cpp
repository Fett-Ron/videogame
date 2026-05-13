#include "SceneLoader.hpp"

#include <glm/glm.hpp>
#include <iostream>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"

SceneLoader::SceneLoader() {
    std::cout << "[SCENELOADER] se ejecuta el constructor" << std::endl;
}

SceneLoader::~SceneLoader() {
    std::cout << "[SCENELOADER] se ejecuta el destructor" << std::endl;
}

void SceneLoader::loadScene(const std::string& scenePath, sol::state& lua
    , std::unique_ptr<AssetManager>& assetManager
    , std::unique_ptr<ControllerManager>& controllerManager
    , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer) {
    
    sol::load_result script_result = lua.load_file(scenePath);
    if (!script_result.valid()) {
        sol::error err = script_result;
        std::string errMessage = err.what();
        std::cerr << "[SCENELOADER] " << errMessage << std::endl;
        return;
    }
    lua.script_file(scenePath);
    sol::table scene = lua["scene"];

    sol::table sprites = scene["sprites"];
    loadSprites(renderer, sprites, assetManager);

    sol::table fonts = scene["fonts"];
    loadFonts(fonts, assetManager);

    sol::table keys = scene["keys"];
    loadKeys(keys, controllerManager);

    sol::table buttons = scene["buttons"];
    loadButtons(buttons, controllerManager);

    sol::table entities = scene["entities"];
    loadEntities(lua, entities, registry);
}

void SceneLoader::loadSprites(SDL_Renderer* renderer, const sol::table& sprites
    , std::unique_ptr<AssetManager>& assetManager) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasSprite = sprites[index];
        if (hasSprite == sol::nullopt) {
            break;
        }
        sol::table sprite = sprites[index];
        std::string assetId = sprite["assetId"];
        std::string filePath = sprite["filePath"];

        assetManager->addTexture(renderer, assetId, filePath);
        index++;
    }
}

void SceneLoader::loadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasFont = fonts[index];
        if (hasFont == sol::nullopt) {
            break;
        }
        sol::table font = fonts[index];
        std::string fontId = font["fontId"];
        std::string filePath = font["filePath"];
        int size = font["fontSize"];
        assetManager->addFont(fontId, filePath, size);

        index++;
    }
}

void SceneLoader::loadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager) {
    int index = 0;
    while(true) {
        sol::optional<sol::table> hasKey = keys[index];
        if (hasKey == sol::nullopt) {
            break;
        }
        sol::table key = keys[index];
        std::string name = key["name"];
        int keyCode = key["key"];
        controllerManager->addActionKey(name, keyCode);
        index++;
    }
}

void SceneLoader::loadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager) {
    int index = 0;
    while(true) {
        sol::optional<sol::table> hasButtons = buttons[index];
        if (hasButtons == sol::nullopt) {
            break;
        }
        sol::table button = buttons[index];
        std::string name = button["name"];
        int buttonCode = button["button"];
        controllerManager->addMouseButton(name, buttonCode);
        index++;
    }
}

void SceneLoader::loadEntities(sol::state& lua, const sol::table& entities
    , std::unique_ptr<Registry>& registry) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasEntity = entities[index];
        if (hasEntity == sol::nullopt) {
            break;
        }
        sol::table entity = entities[index];
        Entity newEntity = registry->createEntity();

        sol::optional<sol::table> hasComponents = entity["components"];
        if (hasComponents != sol::nullopt) {
            sol::table components = entity["components"];
            // agregar animation component
            sol::optional<sol::table> hasAnimation = components["animation"];
            if (hasAnimation != sol::nullopt) {
                newEntity.addComponent<AnimationComponent>(
                    components["animation"]["num_frames"],
                    components["animation"]["speed_rate"],
                    components["animation"]["is_loop"]
                );
            }

            // CircleColliderComponent
            sol::optional<sol::table> hasCircleCollider = components["circle_collider"];
            if (hasCircleCollider != sol::nullopt) {
                newEntity.addComponent<CircleColliderComponent>(
                    components["circle_collider"]["radius"],
                    components["circle_collider"]["width"],
                    components["circle_collider"]["height"]
                );
            }

            // ClickableComponents
            sol::optional<sol::table> hasClickable = components["clickable"];
            if (hasClickable != sol::nullopt) {
                newEntity.addComponent<ClickableComponent>();
            }

            // RigidBodyComponent
            sol::optional<sol::table> hasRigidBody = components["rigid_body"];
            if (hasRigidBody != sol::nullopt) {
                newEntity.addComponent<RigidBodyComponent>(
                    glm::vec2(
                        components["rigid_body"]["velocity"]["x"],
                        components["rigid_body"]["velocity"]["y"]
                    )
                );
            }

            // HealthComponent
            sol::optional<sol::table> hasHealth = components["health"];
            if (hasHealth != sol::nullopt) {
                int maxHealth = components["health"]["max_health"];
                newEntity.addComponent<HealthComponent>(maxHealth);
            }

            // Script Component
            sol::optional<sol::table> hasScript = components["script"];
            if (hasScript != sol::nullopt) {
                lua["onClick"] = sol::nil;
                lua["update"] = sol::nil;

                std::string path = components["script"]["path"];
                lua.script_file(path);

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if (hasOnClick != sol::nullopt) {
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }                                
                newEntity.addComponent<ScriptComponent>(update, onClick);
            }

            // SpriteComponent
            sol::optional<sol::table> hasSprite = components["sprite"];
            if (hasSprite != sol::nullopt) {
                newEntity.addComponent<SpriteComponent>(
                    components["sprite"]["assetId"],
                    components["sprite"]["width"],
                    components["sprite"]["height"],
                    components["sprite"]["src_rect"]["x"],
                    components["sprite"]["src_rect"]["y"]
                );
            }

            sol::optional<sol::table> hasText = components["text"];
            if (hasText != sol::nullopt) {
                newEntity.addComponent<TextComponent>(
                    components["text"]["text"],
                    components["text"]["fontId"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"]
                    
                );
            }

            // TransformComponent
            sol::optional<sol::table> hasTransform = components["transform"];
            if (hasTransform != sol::nullopt) {
                newEntity.addComponent<TransformComponent>(
                    glm::vec2(
                        components["transform"]["position"]["x"],
                        components["transform"]["position"]["y"]
                    ),
                    glm::vec2(
                        components["transform"]["scale"]["x"],
                        components["transform"]["scale"]["y"]
                    ),
                    components["transform"]["rotation"]
                );
            }
        }
        index++;
    }
}