#pragma once
#include "PhysicsProjectile.h"

//������ Ŀ��Ͷ����
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

