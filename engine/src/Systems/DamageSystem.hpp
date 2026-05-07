#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
  public:
    DamageSystem() {
        requiereComponent<CircleColliderComponent>();        
    }

    void subscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager){
        eventManager->subscribeToEvent<CollisionEvent, DamageSystem>(this, &DamageSystem::onCollision);
    }

    void onCollision(CollisionEvent& e){
        std::cout << "[DAMAGESYSTEM] Colision detectada entre " << e.a.getId() 
        << " y " << e.b.getId() << std::endl;
        // Por ahora, deshabilitado para que zombies no se eliminen
        // e.a.kill();
        // e.b.kill();
    }
};

#endif // DAMAGESYSTEM_HPP