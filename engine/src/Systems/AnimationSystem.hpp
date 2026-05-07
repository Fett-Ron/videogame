#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <SDL2/SDL.h>

#include <iostream>

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class AnimationSystem : public System {
  public:
    AnimationSystem() {
        requiereComponent<AnimationComponent>();
        requiereComponent<SpriteComponent>();
    }

    void update() {
        for (auto entity : getSystemEntities()) {
            auto& animation = entity.getComponent<AnimationComponent>();
            auto& sprite = entity.getComponent<SpriteComponent>();

            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) 
                * animation.frameSpeedRate / 1000) % animation.numFrames;
            sprite.srcRect.x = animation.currentFrame * sprite.width;
            //std::cout << "[ANIMATIONSYSTEM] srcRect: " << sprite.srcRect.x << std::endl;
        }
    }
};

#endif // ANIMATIONSYSTEM_HPP