#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <string>

#include "../Components/ClickableComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System {
  public:
    UISystem() {
        requiereComponent<ClickableComponent>();
        requiereComponent<TextComponent>();
        requiereComponent<TransformComponent>();
        requiereComponent<VisibleComponent>();  
    }

    void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->subscribeToEvent<ClickEvent, UISystem>(this, &UISystem::onClickEvent);
    }

    void onClickEvent(ClickEvent& e) {
        for (auto entity : getSystemEntities()) {
            auto& visible = entity.getComponent<VisibleComponent>();
            if (!visible.visible) {
                continue;
            }
            const auto& text = entity.getComponent<TextComponent>();
            const auto& transform = entity.getComponent<TransformComponent>();

            if (transform.position.x < e.posX && e.posX < transform.position.x + text.width
                && transform.position.y < e.posY && e.posY < transform.position.y + text.height){
                if (entity.hasComponent<ScriptComponent>()) {
                    const auto& script = entity.getComponent<ScriptComponent>();
                    if (script.onClick != sol::nil) {
                        script.onClick();
                    }
                }
            }
        }
    }
};

#endif // UISYSTEM_HPP