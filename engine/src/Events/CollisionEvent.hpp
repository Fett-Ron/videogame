#ifndef COLLISSIONEVENT_HPP
#define COLLISSIONEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class CollisionEvent : public Event {
  public:
    Entity a;
    Entity b;

    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif // COLLISSIONEVENT_HPP