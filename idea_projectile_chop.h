#pragma once
#include "PhysicsChara.h"
#include "PhysicsProjectileFlying.h"
#include "Projectile.h"

class idea_projectile_chop :
    public Projectile
{
public:
    static idea_projectile_chop* createNew();

    void setup(int _position_x, int _position_y, CharaDirection direction, bool _flip);

    PhysicsProjectileFlying* getPhysics() const;
protected:
    idea_projectile_chop();
    ~idea_projectile_chop()override;
};

