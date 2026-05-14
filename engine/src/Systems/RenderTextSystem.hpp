#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../AssetManager/AssetManager.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/VisibleComponent.hpp"

class RenderTextSystem : public System {
  public:
    RenderTextSystem(){
        requiereComponent<TextComponent>();
        requiereComponent<TransformComponent>();
        requiereComponent<VisibleComponent>();
    }

    void update(SDL_Renderer* renderer
        , const std::unique_ptr<AssetManager>& assetManager){
        for (auto entity : getSystemEntities()) {
            auto& visible = entity.getComponent<VisibleComponent>();
            if (!visible.visible) {
                continue;
            }
            auto& text = entity.getComponent<TextComponent>();
            auto& transform = entity.getComponent<TransformComponent>();

            SDL_Surface* surface = TTF_RenderText_Blended(assetManager->getFont(text.fontId)
            , text.text.c_str(), text.color);
            text.width = surface->w;
            text.height = surface->h;
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x),
                static_cast<int>(transform.position.y),
                text.width,
                text.height
            };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
};

#endif // RENDERTEXTSYSTEM_HPP