#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function update;
    sol::function onClick;

    ScriptComponent(sol::function update = sol::lua_nil
        , sol::function onClick = sol::lua_nil) {
        this->update = update;
        this->onClick = onClick;
    };
};

#endif // SCRIPTCOMPONENT_HPP