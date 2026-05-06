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
        lua.new_usertype<Entity>("entity");

        // functions
        lua.set_function("is_action_activated", isActionActivated);
        lua.set_function("set_velocity", setVelocity);
        lua.set_function("go_to_scene", goToScene);
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