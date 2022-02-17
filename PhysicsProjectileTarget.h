#pragma once
#include "PhysicsProjectile.h"

//物理体 目标投射物
class PhysicsProjectileTarget :
    public PhysicsProjectile
{
public:
    static PhysicsProjectileTarget* createNew();

    void update() override;

    void setup(PhysicsChara* _target, double _velocity);
	
protected:
    PhysicsProjectileTarget();
    ~PhysicsProjectileTarget()override;

    PhysicsChara* target;
    void setVelocity(double _v);

};

