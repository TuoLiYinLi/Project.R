#pragma once
#include "PhysicsProjectile.h"
class ProjectileFlying :
    public PhysicsProjectile
{
public:
    static ProjectileFlying* createNew();

	void update() override;

    double gravity; //重力

    double x_a; //纵向加速度
    double y_a; //横向加速度

    double damping;    //速度衰减系数

protected:
    ProjectileFlying();
    ~ProjectileFlying()override;

};

