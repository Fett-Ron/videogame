#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

struct HealthComponent {
    int maxHealth;
    int currentHealth;

    HealthComponent(int maxHealth = 10) {
        this->maxHealth = maxHealth;
        this->currentHealth = maxHealth;
    }
};

#endif // HEALTHCOMPONENT_HPP
