#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

// Controles
bool isActionActivated(const std::string& action) {
    return Game::getInstance().controllerManager->isActionActivated(action);
}

// RigidBodyComponent
void setVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

// Scenes
void goToScene(const std::string& sceneName) {
    Game::getInstance().sceneManager->setNextScene(sceneName);
    Game::getInstance().sceneManager->stopScene();
}

#endif // LUABINDING_HPP