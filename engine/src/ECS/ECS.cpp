#include "ECS.hpp"

#include <algorithm>

std::vector<IPool> pools;

int IComponent::nextId = 0;

int Entity::getId() const {
    return id;
}

void Entity::kill() {
    registry->killEntity(*this);
}

void System::addEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity entity) {
    auto it = std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    });
    entities.erase(it, entities.end());
}

std::vector<Entity> System::getSystemEntities() const {
    return entities;
}

const Signature& System::getComponentSignature() const {
    return componentSignature;
}

Entity Registry::createEntity() { // to do: reutilizar ids de entidades eliminadas
    int entityId;
    if (freeIds.empty()) {
        entityId = numEntity++;
        if (static_cast<long unsigned int>(entityId) >= entityComponentSignatures.size()) {
            entityComponentSignatures.resize(entityId + 100);
        }
    } else {
        entityId = freeIds.front();
        freeIds.pop_front();
    }


    Entity entity(entityId);
    entity.registry = this;
    entitiesToBeAdded.insert(entity);
    std::cout << "[Registry] Se crea la entidad con id: " << entity.getId() << std::endl;
    return entity;
}

void Registry::killEntity(Entity entity) {
    entitiesToBeKilled.insert(entity);    
}

void Registry::addEntityToSystems(Entity entity){
    const int entityId = entity.getId();
    const auto& entitySignature = entityComponentSignatures[entityId];
    for (auto& system : systems) {
        const auto& systemComponentSignature = system.second->getComponentSignature();
        bool isInterested = (entitySignature & systemComponentSignature) == systemComponentSignature;
        if (isInterested) {
            system.second->addEntityToSystem(entity);
        }
    }
}

void Registry::removeEntityFromSystems(Entity entity){
    for (auto& system : systems) {
        system.second->removeEntityFromSystem(entity);
    }    
}

void Registry::update() {
    for (auto entity : entitiesToBeAdded) {
        addEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for (auto entity : entitiesToBeKilled) {
        removeEntityFromSystems(entity);
        entityComponentSignatures[entity.getId()].reset();
        freeIds.push_back(entity.getId());
    }
    entitiesToBeKilled.clear();
}   

void Registry::clearAllEntities() {
    for (int i = 0; i < numEntity; i++) {
        Entity entity(i);
        entity.registry = this;
        removeEntityFromSystems(entity);
        entityComponentSignatures[i].reset();
        freeIds.push_back(i);
    }
}