#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <iostream>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class CollisionSystem : public System {
  public:
    CollisionSystem() {
        requiereComponent<CircleColliderComponent>();
        requiereComponent<TransformComponent>();
    }

    void update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = getSystemEntities();
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto aCollider = a.getComponent<CircleColliderComponent>();
            auto aTransform = a.getComponent<TransformComponent>();

            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;
                if (a == b) {
                    continue;
                }
                auto bCollider = b.getComponent<CircleColliderComponent>();
                auto bTransform = b.getComponent<TransformComponent>();

                glm::vec2 aCenterPos = glm::vec2(
                    aTransform.position.x - (aCollider.width / 2) * aTransform.scale.x,
                    aTransform.position.y - (aCollider.height / 2) * aTransform.scale.x
                );
                glm::vec2 bCenterPos = glm::vec2(
                    bTransform.position.x - (bCollider.width / 2) * bTransform.scale.x,
                    bTransform.position.y - (bCollider.height / 2) * bTransform.scale.x
                );

                int aRadius = aCollider.radius * aTransform.scale.x;
                int bRadius = bCollider.radius * bTransform.scale.x;

                bool collision = checkCircularCollision(aRadius, bRadius
                    , aCenterPos, bCenterPos);
                if (collision) {
                    std::cout << "[COLLISIONSYSTEM] Colision entre " << a.getId() 
                    << " y " << b.getId() << std::endl;
                    eventManager->emitEvent<CollisionEvent>(a, b);
                }
            }            
        }
    }

    bool checkCircularCollision(int aRadius, int bRadius
        , glm::vec2 aPos, glm::vec2 bPos) {
        glm::vec2 dif = aPos - bPos;
        double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
        // Hay colisión si la suma de los raios es mayor a la distancia entre los centros
        return (aRadius + bRadius) >= length;
    }
};

#endif // COLLISIONSYSTEM_HPP   