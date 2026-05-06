#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderSystem : public System {
  public:
    RenderSystem() {
        requiereComponent<SpriteComponent>();
        requiereComponent<TransformComponent>();
    }

    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& assetManager) {
        for (auto entity : getSystemEntities()){
            const auto sprite = entity.getComponent<SpriteComponent>();
            const auto transform = entity.getComponent<TransformComponent>();

            SDL_Rect srcRect = sprite.srcRect;
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y)
            };

            SDL_RenderCopyEx(
                renderer,
                assetManager->getTexture(sprite.textureId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                SDL_FLIP_NONE
            );
        }
    }

};

#endif // RENDERSYSTEM_HPP