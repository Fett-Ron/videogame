#ifndef VISIBLECOMPONENT_HPP
#define VISIBLECOMPONENT_HPP

struct VisibleComponent {
    bool visible;

    VisibleComponent(bool visible = true) {
        this->visible = visible;
    }
};

#endif