#pragma once
#include "PhysicsChara.h"
#include "PhysicsProjectileFlying.h"
#include "Projectile.h"

class Facility;
class Chara;

class idea_projectile_chop :
    public Projectile
{
public:
    static idea_projectile_chop* createNew();

    void update() override;

    void setup(AllyType _ally, int _position_x, int _position_y, PhysicsDirection direction, bool _flip);

    PhysicsProjectileFlying* getPhysics() const;
protected:
    idea_projectile_chop();

    integration_recorder<PhysicsChara> recorder_chara;
    integration_recorder<PhysicsFacility> recorder_facility;
};

