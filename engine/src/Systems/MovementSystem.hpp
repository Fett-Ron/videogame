#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"
#include <algorithm>

class MovementSystem : public System {
  private:
    // Límites de la pantalla (800x600)
    const float WINDOW_WIDTH = 800.0f;
    const float WINDOW_HEIGHT = 600.0f;
    
  public:
    MovementSystem() {
        requiereComponent<RigidBodyComponent>();
        requiereComponent<TransformComponent>();
    }

    void update(double dt) {
        for (auto entity : getSystemEntities()) {
            const auto& rigidBody = entity.getComponent<RigidBodyComponent>();
            auto& transform = entity.getComponent<TransformComponent>();
            
            // Actualizar posición
            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;
            
            // Aplicar límites de pantalla
            // Obtener el tamaño del sprite escalado si existe
            float spriteWidth = 0.0f;
            float spriteHeight = 0.0f;
            
            if (entity.hasComponent<SpriteComponent>()) {
                const auto& sprite = entity.getComponent<SpriteComponent>();
                spriteWidth = sprite.width * transform.scale.x;
                spriteHeight = sprite.height * transform.scale.y;
            }
            
            // Clampear posición X
            transform.position.x = std::max(0.0f, transform.position.x);
            transform.position.x = std::min(WINDOW_WIDTH - spriteWidth, transform.position.x);
            
            // Clampear posición Y
            transform.position.y = std::max(0.0f, transform.position.y);
            transform.position.y = std::min(WINDOW_HEIGHT - spriteHeight, transform.position.y);
        }
    }
    
};

#endif // MOVEMENTSYSTEM_HPP