#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Binding/LuaBinding.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/ScriptComponent.hpp"

class ScriptSystem : public System {
  public:
    ScriptSystem() {
        requiereComponent<ScriptComponent>();
    }

    void createLuaBinding(sol::state& lua) {
        // clases
        lua.new_usertype<Entity>("entity",
            "kill", &Entity::kill
        );
        lua.new_usertype<glm::vec2>("vec2",
            "x", &glm::vec2::x,
            "y", &glm::vec2::y
        );

        // functions
        lua.set_function("is_action_activated", isActionActivated);
        lua.set_function("get_position", getPosition);
        lua.set_function("set_position", setPosition);
        lua.set_function("set_velocity", setVelocity);
        lua.set_function("change_animation", changeAnimation);
        lua.set_function("go_to_scene", goToScene);
        lua.set_function("get_time_miliseconds", getTimeMiliseconds);
        lua.set_function("damage_entity", damageEntity);
        lua.set_function("get_health", getHealth);
        lua.set_function("is_entity_dead", isEntityDead);
        lua.set_function("set_text", setText);
        lua.set_function("create_bullet", createBullet);
    }

    void update(sol::state& lua) {
        for (auto entity : getSystemEntities()) {
            const auto& script = entity.getComponent<ScriptComponent>();
            if (script.update != sol::lua_nil) {
                lua["this"] = entity;
                script.update();
            }
        }
    }
};

#endif // SCRIPTSYSTEM_HPP