#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

// Controles
bool isActionActivated(const std::string& action) {
    return Game::getInstance().controllerManager->isActionActivated(action);
}

// TransformComponent
glm::vec2 getPosition(Entity entity) {
    auto& transform = entity.getComponent<TransformComponent>();
    return transform.position;
}

void setPosition(Entity entity, float x, float y) {
    auto& transform = entity.getComponent<TransformComponent>();
    transform.position.x = x;
    transform.position.y = y;
}

// RigidBodyComponent
void setVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

// Cambiar animación y sprite
void changeAnimation(Entity entity, const std::string& assetId, int numFrames, int speedRate, bool isLoop) {
    auto& sprite = entity.getComponent<SpriteComponent>();
    sprite.textureId = assetId;
    sprite.srcRect.x = 0;  // Reiniciar al primer frame
    
    auto& animation = entity.getComponent<AnimationComponent>();
    animation.numFrames = numFrames;
    animation.frameSpeedRate = speedRate;
    animation.isLoop = isLoop;
    animation.currentFrame = 0;
    animation.startTime = SDL_GetTicks();
}

// Scenes
void goToScene(const std::string& sceneName) {
    Game::getInstance().sceneManager->setNextScene(sceneName);
    Game::getInstance().sceneManager->stopScene();
}

#endif // LUABINDING_HPP