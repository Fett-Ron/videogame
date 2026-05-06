#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System {
  public:
    MovementSystem() {
        requiereComponent<RigidBodyComponent>();
        requiereComponent<TransformComponent>();
    }

    void update(double dt) {
        for (auto entity : getSystemEntities()) {
            const auto& rigidBody = entity.getComponent<RigidBodyComponent>();
            auto& transform = entity.getComponent<TransformComponent>();

            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;
        }
    }
    
};

#endif // MOVEMENTSYSTEM_HPP