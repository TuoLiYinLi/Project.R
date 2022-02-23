#pragma once
#include "PhysicsProjectile.h"
#include "Projectile.h"
class Facility;
enum class PhysicsDirection;

class idea_projectile_little_slime_ball :
    public Projectile
{
public:
    static idea_projectile_little_slime_ball* createNew();

    void update() override;

    void setup(AllyType _ally, int _position_x, int _position_y, bool direction_right);

    PhysicsProjectile* getPhysics() const;
protected:
    idea_projectile_little_slime_ball();
};

