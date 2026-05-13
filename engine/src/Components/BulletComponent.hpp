#ifndef BULLETCOMPONENT_HPP
#define BULLETCOMPONENT_HPP

struct BulletComponent {
    int damage = 1;
    
    BulletComponent(int dmg = 1) : damage(dmg) {}
};

#endif // BULLETCOMPONENT_HPP
