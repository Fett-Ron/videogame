#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/BulletComponent.hpp"
#include "../Components/ZombieComponent.hpp"
#include "../Components/VisibleComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

inline int aliveZombies = 0;
inline int totalZombiesKilled = 0;
inline bool gameOver = false;
inline bool paused = false;

// Controles
inline bool isActionActivated(const std::string& action) {
    return Game::getInstance().controllerManager->isActionActivated(action);
}

// TransformComponent
inline glm::vec2 getPosition(Entity entity) {
    auto& transform = entity.getComponent<TransformComponent>();
    return transform.position;
}

inline void setPosition(Entity entity, float x, float y) {
    auto& transform = entity.getComponent<TransformComponent>();
    transform.position.x = x;
    transform.position.y = y;
}

// RigidBodyComponent
inline void setVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

// Cambiar animación y sprite
inline void changeAnimation(Entity entity, const std::string& assetId, int numFrames, int speedRate, bool isLoop) {
    auto& sprite = entity.getComponent<SpriteComponent>();
    sprite.textureId = assetId;
    auto& animation = entity.getComponent<AnimationComponent>();
    animation.numFrames = numFrames;
    animation.frameSpeedRate = speedRate;
    animation.isLoop = isLoop;
    animation.currentFrame = 0;
    animation.startTime = SDL_GetTicks();
}

// Scenes
inline void goToScene(const std::string& sceneName) {
    Game::getInstance().sceneManager->setNextScene(sceneName);
    Game::getInstance().sceneManager->stopScene();
}

// Time
inline int getTimeMiliseconds() {
    return SDL_GetTicks();
}

// Health
inline void damageEntity(Entity entity, int damage) {
    auto& health = entity.getComponent<HealthComponent>();
    std::cout << "daño recibido" << std::endl;
    health.currentHealth -= damage;
    if (health.currentHealth < 0) {
        health.currentHealth = 0;
    }
}

inline int getHealth(Entity entity) {
    auto& health = entity.getComponent<HealthComponent>();
    return health.currentHealth;
}

inline bool isEntityDead(Entity entity) {
    auto& health = entity.getComponent<HealthComponent>();
    return health.currentHealth <= 0;
}

// Text
inline void setText(Entity entity, const std::string& text) {
    auto& textComponent = entity.getComponent<TextComponent>();
    textComponent.text = text;
}

// Bullets
inline Entity createBullet(float x, float y, std::string direccion) {
    auto& registry = *Game::getInstance().registry;
    auto& lua = Game::getInstance().lua;
    
    Entity bullet = registry.createEntity();
    int speed = 300;
    glm::vec2 velocity = glm::vec2(0,0);
    if (direccion == "up") {
        velocity = glm::vec2(0, -speed);
    } else if (direccion == "down") {
        velocity = glm::vec2(0, speed);
    } else if (direccion == "side") {
        velocity = glm::vec2(speed, 0);
    } else if (direccion == "side_left") {
        velocity = glm::vec2(-speed, 0);
    }
    
    // Add components
    bullet.addComponent<TransformComponent>(glm::vec2(x, y), glm::vec2(1.0f, 1.0f), 0.0);
    bullet.addComponent<SpriteComponent>("bullet", 4, 4);
    bullet.addComponent<RigidBodyComponent>(velocity);
    bullet.addComponent<CircleColliderComponent>(2, 4, 4);
    bullet.addComponent<BulletComponent>(1);  // 1 punto de daño

    // Load bullet script
    lua["update"] = sol::nil;
    lua.script_file("./assets/scripts/bullet.lua");
    
    sol::optional<sol::function> hasUpdate = lua["update"];
    sol::function update = sol::nil;
    if(hasUpdate != sol::nullopt){
        update = lua["update"];
    }
    
    bullet.addComponent<ScriptComponent>(update, sol::lua_nil);
    
    return bullet;
}

inline void playGunshotSound() {
    Game::getInstance().playGunshotSound();
}

inline Entity spawnZombie(float x, float y) {
    auto& registry = *Game::getInstance().registry;
    auto& lua = Game::getInstance().lua;

    Entity zombie = registry.createEntity();

    zombie.addComponent<TransformComponent>(
        glm::vec2(x, y),
        glm::vec2(2.0f, 2.0f),
        0.0
    );

    zombie.addComponent<SpriteComponent>(
        "zombie_idle_down",
        16,
        16
    );

    zombie.addComponent<AnimationComponent>(
        6,
        10,
        true
    );

    zombie.addComponent<RigidBodyComponent>(
        glm::vec2(0,0)
    );

    zombie.addComponent<CircleColliderComponent>(
        8,
        16,
        16
    );

    zombie.addComponent<HealthComponent>(5);

    zombie.addComponent<ZombieComponent>();

    // cargar script
    lua["update"] = sol::nil;
    lua.script_file("./assets/scripts/zombie.lua");

    sol::optional<sol::function> hasUpdate =
        lua["update"];

    sol::function update = sol::lua_nil;

    if(hasUpdate != sol::nullopt){
        update = lua["update"];
    }

    zombie.addComponent<ScriptComponent>(
        update,
        sol::lua_nil
    );
    aliveZombies++;
    return zombie;
}

inline int getAliveZombies() {
    return aliveZombies;
}

inline int getTotalZombiesKilled() {
    return totalZombiesKilled;
}

inline bool isGameOver() {
    return gameOver;
}

inline void setGameOver(bool value) {
    gameOver = value;
}

inline void setTextColor(Entity entity, int r, int g, int b, int a) {
    auto& text = entity.getComponent<TextComponent>();

    text.color.r = r;
    text.color.g = g;
    text.color.b = b;
    text.color.a = a;
}

inline void setVisible(Entity entity, bool visible) {
    auto& visibleComponent =
        entity.getComponent<VisibleComponent>();

    visibleComponent.visible = visible;
}

inline bool isPaused() {
    return paused;
}

inline void setPaused(bool value) {
    paused = value;
}

#endif // LUABINDING_HPP