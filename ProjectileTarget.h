#pragma once
#include "PhysicsProjectile.h"
class ProjectileTarget :
    public PhysicsProjectile
{
public:
    static ProjectileTarget* createNew();

    void update() override;

    PhysicsChara* target;
protected:
    ProjectileTarget();
    ~ProjectileTarget()override;

private:
    void setVelocity(double _v);
};

