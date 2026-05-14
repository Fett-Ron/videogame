#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/BulletComponent.hpp"
#include "../Components/ZombieComponent.hpp"
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
        bool eA_hasZombie = e.a.hasComponent<ZombieComponent>();
        bool eB_hasZombie = e.b.hasComponent<ZombieComponent>();
        
        // Caso 1: e.a es bala y e.b es zombie
        if (eA_hasBullet && eB_hasZombie) {
            auto& bulletA = e.a.getComponent<BulletComponent>();
            auto& healthB = e.b.getComponent<HealthComponent>();
            healthB.currentHealth -= bulletA.damage;
            std::cout << "[DAMAGESYSTEM] Bala daña a zombie. Salud: " << healthB.currentHealth << std::endl;
            if (healthB.currentHealth <= 0) {
                std::cout << "[DAMAGESYSTEM] Zombie eliminado" << std::endl;
                aliveZombies--;
                totalZombiesKilled++;
                e.b.kill();
            }
            e.a.kill();  // Bala desaparece
        }
        // Caso 2: e.b es bala y e.a es zombie
        else if (eB_hasBullet && eA_hasZombie) {
            auto& bulletB = e.b.getComponent<BulletComponent>();
            auto& healthA = e.a.getComponent<HealthComponent>();
            healthA.currentHealth -= bulletB.damage;
            std::cout << "[DAMAGESYSTEM] Bala daña a zombie. Salud: " << healthA.currentHealth << std::endl;
            if (healthA.currentHealth <= 0) {
                std::cout << "[DAMAGESYSTEM] Zombie eliminado" << std::endl;
                aliveZombies--;
                totalZombiesKilled++;
                e.a.kill();
            }
            e.b.kill();  // Bala desaparece
        }
    }
};

#endif // DAMAGESYSTEM_HPP