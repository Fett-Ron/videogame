#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/BulletComponent.hpp"
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
        bool eA_hasBullet = e.a.hasComponent<BulletComponent>();
        bool eB_hasBullet = e.b.hasComponent<BulletComponent>();
        bool eA_hasHealth = e.a.hasComponent<HealthComponent>();
        bool eB_hasHealth = e.b.hasComponent<HealthComponent>();
        
        // Caso 1: e.a es bala y e.b es zombie
        if (eA_hasBullet && eB_hasHealth) {
            auto& bulletA = e.a.getComponent<BulletComponent>();
            auto& healthB = e.b.getComponent<HealthComponent>();
            healthB.currentHealth -= bulletA.damage;
            std::cout << "[DAMAGESYSTEM] Bala daña a zombie. Salud: " << healthB.currentHealth << std::endl;
            if (healthB.currentHealth <= 0) {
                std::cout << "[DAMAGESYSTEM] Zombie eliminado" << std::endl;
                e.b.kill();
            }
            e.a.kill();  // Bala desaparece
        }
        // Caso 2: e.b es bala y e.a es zombie
        else if (eB_hasBullet && eA_hasHealth) {
            auto& bulletB = e.b.getComponent<BulletComponent>();
            auto& healthA = e.a.getComponent<HealthComponent>();
            healthA.currentHealth -= bulletB.damage;
            std::cout << "[DAMAGESYSTEM] Bala daña a zombie. Salud: " << healthA.currentHealth << std::endl;
            if (healthA.currentHealth <= 0) {
                std::cout << "[DAMAGESYSTEM] Zombie eliminado" << std::endl;
                e.a.kill();
            }
            e.b.kill();  // Bala desaparece
        }
    }
};

#endif // DAMAGESYSTEM_HPP